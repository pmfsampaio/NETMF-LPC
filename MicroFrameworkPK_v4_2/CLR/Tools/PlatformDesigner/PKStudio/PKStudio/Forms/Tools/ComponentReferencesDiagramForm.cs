using System.Windows.Forms;
using WeifenLuo.WinFormsUI.Docking;
using Dalssoft.DiagramNet;
using System.Drawing;
using System.Collections.Generic;
using System;
using System.Drawing.Drawing2D;
using PKStudio.ItemWrappers;

namespace PKStudio.Forms.Tools
{
    public partial class ComponentReferencesDiagramForm : PKStudio.Forms.BaseForms.BasePKInventoryForm
    {
        [Serializable]
        private class MFRectangleNode : RoundRectangleNode
        {
            public MFRectangleNode(Point l, Size s)
                : base(l, s)
            {
            }
            public object Tag { get; set; }


        }

        //Ru: Класс, содержащий отображаемые на диаграмме объекты
        //En: Class contains objects that shown on diagram
        private class HierarchyCollection
        {
            public HierarchyCollection()
            {
            }

            //Ru: Описание связи между компонентами
            //En: Components references description
            public class Link
            {
                public enum LINK_TYPE
                {
                    Dependency,
                    Realise,
                    Associate,
                    Stub
                }

                public Link(LINK_TYPE type, ComponentWrapper start, ComponentWrapper end)
                {
                    this.Type = type;
                    this.StartComponent = start;
                    this.EndComponent = end;
                }

                public bool IsEqual(Link link)
                {
                    if (this.EndComponent.Guid.ToLower() != link.EndComponent.Guid.ToLower()) return false;
                    if (this.StartComponent.Guid.ToLower() != link.StartComponent.Guid.ToLower()) return false;
                    if (this.Type != link.Type) return false;
                    return true;
                }


                public LINK_TYPE Type { get; set; }

                public ComponentWrapper StartComponent { get; set; }
                public ComponentWrapper EndComponent { get; set; }
            }

            public List<ComponentWrapper> Featuries = new List<ComponentWrapper>();
            public List<ComponentWrapper> LibraryCategories = new List<ComponentWrapper>();
            public List<ComponentWrapper> Librares = new List<ComponentWrapper>();

            public List<Link> Links = new List<Link>();

            //Ru: Анализатор компонента, вносящий в список все связанные с ним компоненты
            //En: Analizes component and adds all its references
            public void AnalyseComponent(ComponentWrapper comp)
            {
                Link l;
                if (comp != null)
                {
                    switch (comp.ComponentType)
                    {
                        #region Library
                        case ComponentTypeWrapper.Library:
                            LibraryWrapper lib = PK.Wrapper.FindLibrary(comp);
                            if (lib != null)
                            {
                                //Ru: Заносим себя в список
                                //En: add itself to the list
                                if (!ContainsLibrary(comp))
                                    Librares.Add(comp);

                                if (lib.HasLibraryCategory)//En: if the library has a library category add it to the list. Ru: Если есть LibCat, то заносим и ее в список
                                {
                                    if (!ContainsLibCat(lib.LibraryCategory))
                                        LibraryCategories.Add(lib.LibraryCategory);
                                    //Связь Lib реализует LibCat
                                    l = new Link(Link.LINK_TYPE.Realise, comp, lib.LibraryCategory);
                                    if (!ContainsLink(l))
                                        Links.Add(l);
                                }
                                //Ru: Заносим в список все Dependency
                                //En: Add all dependencies to the list
                                foreach (ComponentWrapper dep in lib.Dependencies)
                                {
                                    switch (dep.ComponentType)
                                    {
                                        case ComponentTypeWrapper.Library:
                                            if (!ContainsLibrary(dep))
                                                Librares.Add(dep);

                                            //Ru: Связь Lib требует Dependency lib
                                            //En: Add library dependency link
                                            l = new Link(Link.LINK_TYPE.Dependency, comp, dep);
                                            if (!ContainsLink(l))
                                                Links.Add(l);

                                            break;
                                        case ComponentTypeWrapper.Feature:
                                            if (!ContainsFeature(dep))
                                                Featuries.Add(dep);

                                            //Ru: Связь Lib требует Dependency Feature
                                            //En: Add Feature dependency link
                                            l = new Link(Link.LINK_TYPE.Dependency, comp, dep);
                                            if (!ContainsLink(l))
                                                Links.Add(l);

                                            break;
                                        case ComponentTypeWrapper.LibraryCategory:
                                            if (!ContainsLibCat(dep))
                                                LibraryCategories.Add(dep);

                                            //Ru: Связь Lib требует Dependency LibraryCategory
                                            //En: Add Library Category dependency link
                                            l = new Link(Link.LINK_TYPE.Dependency, comp, dep);
                                            if (!ContainsLink(l))
                                                Links.Add(l);

                                            break;
                                    }
                                }

                                foreach (FeatureWrapper FW in PK.Wrapper.GetFeatures())
                                {
                                    foreach (ComponentWrapper dep in FW.ComponentDependencies)
                                    {
                                        if (string.Compare(dep.Guid, lib.Guid, true) == 0)
                                        {
                                            ComponentWrapper featdep = ComponentWrapper.GetComponentWrapper(FW);
                                            if (!ContainsFeature(featdep))
                                                Featuries.Add(featdep);
                                            //Связь 
                                            l = new Link(Link.LINK_TYPE.Dependency, featdep, comp);
                                            if (!ContainsLink(l))
                                                Links.Add(l);
                                        }
                                    }
                                }
                            }
                            break;
                        #endregion
                        #region Library Category
                        case ComponentTypeWrapper.LibraryCategory:
                            LibraryCategoryWrapper libcat = PK.Wrapper.FindLibraryCategory(comp.Guid);
                            if (libcat != null)
                            {
                                //Ru: Заносим себя в список
                                //En: add itself to the list
                                if (!ContainsLibCat(comp))
                                    LibraryCategories.Add(comp);

                                foreach (ComponentWrapper asc in libcat.FeatureAssociations)
                                {
                                    if (!ContainsFeature(asc))
                                        Featuries.Add(asc);
                                    //Ru: Связь 
                                    //En: Link
                                    l = new Link(Link.LINK_TYPE.Associate, comp, asc);
                                    if (!ContainsLink(l))
                                        Links.Add(l);
                                }

                                if ((libcat.StubLibrary != null) && (!string.IsNullOrEmpty(libcat.StubLibrary.Guid)))
                                {
                                    if (!ContainsLibrary(libcat.StubLibrary))
                                        Librares.Add(libcat.StubLibrary);

                                    l = new Link(Link.LINK_TYPE.Stub, comp, libcat.StubLibrary);
                                    if (!ContainsLink(l))
                                        Links.Add(l);
                                }
                                foreach (FeatureWrapper feature in PK.Wrapper.GetFeatures())
                                {
                                    foreach (ComponentWrapper dependency in feature.ComponentDependencies)
                                    {
                                        if (dependency.ComponentType == ComponentTypeWrapper.LibraryCategory)
                                        {
                                            if (comp.Equals(dependency))
                                            {
                                                ComponentWrapper featurecomp = ComponentWrapper.GetComponentWrapper(feature);
                                                if (Featuries.Contains(featurecomp) == false)
                                                    Featuries.Add(featurecomp);
                                                l = new Link(Link.LINK_TYPE.Dependency, featurecomp, comp);
                                                if (!ContainsLink(l))
                                                    Links.Add(l);
                                            }
                                        }
                                    }
                                }

                                foreach (LibraryWrapper loclib in PK.Wrapper.GetLibraries())
                                {
                                    if (loclib.HasLibraryCategory)
                                    {
                                        if (loclib.LibraryCategory.Guid.ToLower() == comp.Guid.ToLower())
                                        {
                                            ComponentWrapper libcomp = ComponentWrapper.GetComponentWrapper(loclib);
                                            if (!ContainsLibrary(libcomp))
                                                Librares.Add(libcomp);
                                            l = new Link(Link.LINK_TYPE.Realise, libcomp, comp);
                                            if (!ContainsLink(l))
                                                Links.Add(l);
                                        }
                                    }
                                    foreach (ComponentWrapper dependency in loclib.Dependencies)
                                    {
                                        if (dependency.Equals(comp))
                                        {
                                            ComponentWrapper libcomp = ComponentWrapper.GetComponentWrapper(loclib);
                                            switch (libcomp.ComponentType)
                                            {
                                                case ComponentTypeWrapper.Library:
                                                    if (!ContainsLibrary(libcomp))
                                                        Librares.Add(libcomp);
                                                    break;
                                                case ComponentTypeWrapper.LibraryCategory:
                                                    if (!ContainsLibCat(libcomp))
                                                        LibraryCategories.Add(libcomp);
                                                    break;
                                                default:
                                                    break;
                                            }
                                            l = new Link(Link.LINK_TYPE.Dependency, libcomp, comp);
                                            if (!ContainsLink(l))
                                                Links.Add(l);
                                        }
                                    }
                                }


                            }
                            break;
                        #endregion
                        #region Feature
                        case ComponentTypeWrapper.Feature:
                            FeatureWrapper feat = PK.Wrapper.FindFeature(comp.Guid);
                            if (feat != null)
                            {
                                //Ru: Заносим себя в список
                                //En: add itself to the list
                                if (!ContainsFeature(comp))
                                    Featuries.Add(comp);

                                foreach (ComponentWrapper dep in feat.FeatureDependencies)
                                {
                                    if (!ContainsFeature(dep))
                                        Featuries.Add(dep);
                                    //Ru: Связь 
                                    //En: Link
                                    l = new Link(Link.LINK_TYPE.Dependency, comp, dep);
                                    if (!ContainsLink(l))
                                        Links.Add(l);
                                }

                                //Ru: Заносим в список все Dependency
                                //En: Add all dependencies to the list
                                foreach (ComponentWrapper dep in feat.ComponentDependencies)
                                {
                                    switch (dep.ComponentType)
                                    {
                                        case ComponentTypeWrapper.Library:
                                            if (!ContainsLibrary(dep))
                                                Librares.Add(dep);

                                            //Ru: Связь Lib требует Dependency lib
                                            //En: Add library dependency link
                                            l = new Link(Link.LINK_TYPE.Dependency, comp, dep);
                                            if (!ContainsLink(l))
                                                Links.Add(l);

                                            break;
                                        case ComponentTypeWrapper.Feature:
                                            if (!ContainsFeature(dep))
                                                Featuries.Add(dep);

                                            //Ru: Связь Lib требует Dependency Feature
                                            //En: Add feature dependency link
                                            l = new Link(Link.LINK_TYPE.Dependency, comp, dep);
                                            if (!ContainsLink(l))
                                                Links.Add(l);

                                            break;
                                        case ComponentTypeWrapper.LibraryCategory:
                                            if (!ContainsLibCat(dep))
                                                LibraryCategories.Add(dep);

                                            //Ru: Связь Lib требует Dependency LibraryCategory
                                            //En: Add library category dependency link
                                            l = new Link(Link.LINK_TYPE.Dependency, comp, dep);
                                            if (!ContainsLink(l))
                                                Links.Add(l);

                                            break;
                                    }
                                }

                                foreach (LibraryCategoryWrapper loclibcat in PK.Wrapper.GetLibraryCategories())
                                {
                                    foreach (ComponentWrapper fetasscomp in loclibcat.FeatureAssociations)
                                    {
                                        if (fetasscomp.Guid.ToLower() == comp.Guid.ToLower())
                                        {
                                            ComponentWrapper libcatcomp = ComponentWrapper.GetComponentWrapper(loclibcat);

                                            //Ru: Заносим себя в список
                                            //En: Add itself to the list
                                            if (!ContainsLibCat(libcatcomp))
                                                LibraryCategories.Add(libcatcomp);

                                            //Ru: Связь
                                            //En: Link
                                            l = new Link(Link.LINK_TYPE.Associate, libcatcomp, comp);
                                            if (!ContainsLink(l))
                                                Links.Add(l);
                                        }
                                    }
                                }
                            }
                            break;
                        #endregion
                    }
                }
            }

            private bool ContainsLink(Link link)
            {
                foreach (Link l in Links)
                {
                    if (link.IsEqual(l)) return true;
                }
                return false;
            }

            private bool ContainsFeature(ComponentWrapper feat)
            {
                foreach (ComponentWrapper f in this.Featuries)
                {
                    if (f.Guid.ToLower() == feat.Guid.ToLower()) return true;
                }
                return false;
            }

            private bool ContainsLibCat(ComponentWrapper libcat)
            {
                foreach (ComponentWrapper lc in this.LibraryCategories)
                {
                    if (lc.Guid.ToLower() == libcat.Guid.ToLower()) return true;
                }
                return false;
            }

            private bool ContainsLibrary(ComponentWrapper lib)
            {
                foreach (ComponentWrapper l in this.Librares)
                {
                    if (l.Guid.ToLower() == lib.Guid.ToLower()) return true;
                }
                return false;
            }
        }

        //object obj = null;

        HierarchyCollection collection;

        string lastZoom = "";

        bool CtrlPressed = false;

        public ComponentReferencesDiagramForm()
        {
            InitializeComponent();
            collection = new HierarchyCollection();

            this.designer1.AutoScroll = true;
            this.designer1.DrawGrid = false;

            ClearAllElements();

            ResetZoom();
            lastZoom = toolStripZoomCB.Text;

            designer1.MouseWheel += new MouseEventHandler(designer1_MouseWheel);

        }

        public void SetObject(object obj)
        {
            //this.obj = obj;            

            if (obj != null)
            {
                ClearAllElements();

                if (obj is ComponentWrapper)
                {
                    collection.AnalyseComponent(obj as ComponentWrapper);
                }
                //else if (obj is ProcessorWrapper)
                //{
                //    //text = "Processor: " + ((Processor)obj).Name;
                //}
                //else if (obj is ProjectWrapper)
                //{
                //    //text = "MFProject: " + ((MFProject)obj).Name;
                //}
                //else if (obj is SolutionWrapper)
                //{
                //    //text = "MFSolution: " + ((MFSolution)obj).Name;
                //}
                else if (obj is LibraryCategoryWrapper)
                {
                    collection.AnalyseComponent(ComponentWrapper.GetComponentWrapper(obj as LibraryCategoryWrapper));
                }
                else if (obj is FeatureWrapper)
                {
                    collection.AnalyseComponent(ComponentWrapper.GetComponentWrapper(obj as FeatureWrapper));
                }
                else if (obj is LibraryWrapper)
                {
                    collection.AnalyseComponent(ComponentWrapper.GetComponentWrapper(obj as LibraryWrapper));
                }

                Visualize(collection);
            }
        }

        private void Visualize(HierarchyCollection collection)
        {
            designer1.Document.SelectAllElements();
            designer1.Document.DeleteSelectedElements();
            designer1.Document.ClearSelection();

            ResetZoom();

            int FeatureLineY = 50;
            int LibraryCategoryLineY = 150;
            int LibraryLineY = 250;

            int ElementDistance = 150;

            int count = 1;
            foreach (ComponentWrapper comp in collection.Librares)
            {
                LibraryWrapper LW = PK.Wrapper.FindLibrary(comp.Guid);
                if ((LW != null) && (!string.IsNullOrEmpty(comp.Guid)))
                {
                    AddNodeElement(LW.Name, comp.ComponentType, new Point(count * ElementDistance, LibraryLineY), comp);
                }
                count++;
            }

            count = 1;
            foreach (ComponentWrapper comp in collection.LibraryCategories)
            {
                LibraryCategoryWrapper LCW = PK.Wrapper.FindLibraryCategory(comp.Guid);
                if ((LCW != null) && (!string.IsNullOrEmpty(comp.Guid)))
                {
                    AddNodeElement(LCW.Name, comp.ComponentType, new Point(count * ElementDistance, LibraryCategoryLineY), comp);
                }
                count++;
            }

            count = 1;
            foreach (ComponentWrapper comp in collection.Featuries)
            {
                FeatureWrapper FW = PK.Wrapper.FindFeature(comp.Guid);
                if ((FW != null) && (!string.IsNullOrEmpty(comp.Guid)))
                {
                    AddNodeElement(FW.Name, comp.ComponentType, new Point(count * ElementDistance, FeatureLineY), comp);
                }
                count++;
            }

            foreach (HierarchyCollection.Link link in collection.Links)
            {
                MFRectangleNode StartNode = null;
                MFRectangleNode EndNode = null;
                foreach (BaseElement element in designer1.Document.Elements)
                {
                    if (element.GetType() == typeof(MFRectangleNode))
                    {
                        MFRectangleNode RectNode = (MFRectangleNode)element;
                        if (link.StartComponent.Guid.ToLower() == ((ComponentWrapper)RectNode.Tag).Guid.ToLower()) StartNode = RectNode;
                        if (link.EndComponent.Guid.ToLower() == ((ComponentWrapper)RectNode.Tag).Guid.ToLower()) EndNode = RectNode;
                    }
                }

                if ((StartNode != null) && (EndNode != null))
                {
                    switch (link.Type)
                    {
                        case HierarchyCollection.Link.LINK_TYPE.Dependency:
                            AddLinkElement("Depend", StartNode, 4, LineCap.RoundAnchor, EndNode, 4, LineCap.ArrowAnchor, Color.Red,-10,-10);
                            break;
                        case HierarchyCollection.Link.LINK_TYPE.Realise:
                            AddLinkElement("Realise", StartNode, 4, LineCap.RoundAnchor, EndNode, 4, LineCap.ArrowAnchor, Color.Blue,-10,-10);
                            break;
                        case HierarchyCollection.Link.LINK_TYPE.Stub:
                            AddLinkElement("Stub", StartNode, 5, LineCap.RoundAnchor, EndNode, 5, LineCap.ArrowAnchor, Color.Black,10,10);
                            break;
                        case HierarchyCollection.Link.LINK_TYPE.Associate:
                            AddLinkElement("Associate with", StartNode, 5, LineCap.RoundAnchor, EndNode, 5, LineCap.ArrowAnchor, Color.Green,10,10);
                            break;
                    }
                }
                else
                {
                }
            }


        }

        private MFRectangleNode AddNodeElement(string caption, ComponentTypeWrapper type, Point location, object tag)
        {
            MFRectangleNode rn = new MFRectangleNode(location, new Size(100, 50));

            rn.Tag = tag;

            switch (type)
            {
                case ComponentTypeWrapper.Library:
                    LibraryWrapper l = PK.Wrapper.FindLibrary((ComponentWrapper)tag);
                    if (l != null)
                    {
                        if (l.IsStub)
                        {
                            rn.FillColor1 = Color.Gray;
                            rn.FillColor2 = Color.White;
                        }
                        else
                        {
                            rn.FillColor1 = Color.LightSteelBlue;
                            rn.FillColor2 = Color.White;
                        }
                    }
                    else
                    {
                        rn.FillColor1 = Color.LightSteelBlue;
                        rn.FillColor2 = Color.White;
                    }
                    break;
                case ComponentTypeWrapper.Feature:
                    rn.FillColor1 = Color.Khaki;
                    rn.FillColor2 = Color.White;
                    break;
                case ComponentTypeWrapper.MFAssembly:
                    break;
                case ComponentTypeWrapper.MFSolution:
                    break;
                case ComponentTypeWrapper.Processor:
                    break;
                case ComponentTypeWrapper.OperatingSystem:
                    break;
                case ComponentTypeWrapper.BuildTool:
                    break;
                case ComponentTypeWrapper.ISA:
                    break;
                case ComponentTypeWrapper.BuildParameter:
                    break;
                case ComponentTypeWrapper.LibraryCategory:
                    rn.FillColor1 = Color.LightGreen;
                    rn.FillColor2 = Color.White;
                    break;
                case ComponentTypeWrapper.Unknown:
                    break;
                default:
                    break;
            }

            rn.Label.ReadOnly = true;
            rn.Label.Text = caption;

            rn.Label.Location = rn.Location;
            rn.Label.Size = rn.Size;

            designer1.Document.AddElement(rn);
            UpdateScrolls();
            return rn;
        }

        private StraightLinkElement AddLinkElement(string text, RectangleNode node1, int Node1connector, LineCap StartNodeAnchor, RectangleNode node2, int Node2connector, LineCap EndNodeAnchor, Color color)
        {
            return AddLinkElement(text, node1, Node1connector, StartNodeAnchor, node2, Node2connector, EndNodeAnchor, color, 0,0);
        }

        private StraightLinkElement AddLinkElement(string text, RectangleNode node1, int Node1connector, LineCap StartNodeAnchor, RectangleNode node2, int Node2connector, LineCap EndNodeAnchor, Color color, int XCor,int YCor)
        {
            //RightAngleLinkElement link = new RightAngleLinkElement(node1.Connectors[1], node2.Connectors[0]);

            AdvancedStraightLinkElement link = new AdvancedStraightLinkElement(node1, node1.Connectors[Node1connector], node2, node2.Connectors[Node2connector]);

            link.BorderWidth = 5;
            link.BorderColor = color;
            link.Opacity = 30;
            link.StartCap = StartNodeAnchor;
            link.EndCap = EndNodeAnchor;

            link.Label.ReadOnly = true;
            link.Label.Text = text;

            //link.Label.Location = new Point(link.Location.X+sizeChange,link.Location.Y+sizeChange);
            link.Label.XLocationCorection = XCor;
            link.Label.YLocationCorection = YCor;
            link.Label.Location = link.Location;
            link.Label.Size = link.Size;

            //link.Label.Size = new Size(link.Size.Width + sizeChange, link.Size.Height + sizeChange);


            designer1.Document.AddElement(link);

            return link;
        }

        private void UpdateScrolls()
        {
            designer1.AutoScrollMinSize = new Size((int)((designer1.Document.Location.X + designer1.Document.Size.Width) * designer1.Document.Zoom), (int)((designer1.Document.Location.Y + designer1.Document.Size.Height) * designer1.Document.Zoom));
        }

        public void ClearAllElements()
        {
            collection = new HierarchyCollection();
        }

        private void toolStripButton1_Click(object sender, EventArgs e)
        {
            designer1.Document.SelectAllElements();
        }

        #region Zoom

        void designer1_MouseWheel(object sender, MouseEventArgs e)
        {
            if (CtrlPressed)
            {
                string zoomstr = "";
                int reszoom;

                zoomstr = toolStripZoomCB.Text.Replace("%", "");

                if (int.TryParse(zoomstr, out reszoom))
                {
                    if (e.Delta > 0)
                    {
                        if ((reszoom + 5) < 1000)
                            this.SetZoom((reszoom + 5).ToString() + "%");
                    }
                    else
                    {
                        if ((reszoom - 5) > 0)
                            this.SetZoom((reszoom - 5).ToString() + "%");
                    }
                }
            }
        }

        private void toolStripZoomCB_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.KeyCode == Keys.Enter)
            {
                SetZoom(toolStripZoomCB.Text);
            }
        }

        private void toolStripZoomCB_SelectedIndexChanged(object sender, EventArgs e)
        {
            SetZoom(toolStripZoomCB.Text);
        }

        private void SetZoom(string percent)
        {
            string zoomstr = "";
            int reszoom;

            if (percent.Contains("%")) zoomstr = percent.Replace("%", "");
            else zoomstr = percent;

            if (int.TryParse(zoomstr, out reszoom))
            {
                toolStripZoomCB.Text = reszoom.ToString() + "%";
                designer1.Document.Zoom = (float)reszoom / 100f;
                lastZoom = toolStripZoomCB.Text;
                UpdateScrolls();
            }
            else
            {
                toolStripZoomCB.Text = lastZoom;
            }
        }
        private void toolStripZoomCB_Leave(object sender, EventArgs e)
        {
            toolStripZoomCB.Text = lastZoom;
        }

        private void ResetZoom()
        {
            toolStripZoomCB.SelectedIndex = 4;
        }

        private void ZoomtoolStripMenuItem_Click(object sender, EventArgs e)
        {
            ToolStripMenuItem item = (ToolStripMenuItem)sender;

            SetZoom(item.Text);
        }

        #endregion

        private void designer1_ElementSelection(object sender, ElementSelectionEventArgs e)
        {
            if (e.Elements.Count > 0)
            {
                if (e.Elements[0].GetType() == typeof(MFRectangleNode))
                {
                    MFRectangleNode RectNode = (MFRectangleNode)e.Elements[0];
                    ComponentWrapper comp = (ComponentWrapper)RectNode.Tag;

                    switch (comp.ComponentType)
                    {
                        case ComponentTypeWrapper.Library:
                            LibraryWrapper lib = PK.Wrapper.FindLibrary(comp.Guid);
                            if (lib != null)
                            {
                                this.OnSelectionChangeEvent(lib);
                            }
                            break;
                        case ComponentTypeWrapper.Feature:
                            FeatureWrapper feat = PK.Wrapper.FindFeature(comp.Guid);
                            if (feat != null)
                            {
                                this.OnSelectionChangeEvent(feat);
                            }
                            break;
                        case ComponentTypeWrapper.MFAssembly:
                            break;
                        case ComponentTypeWrapper.MFSolution:
                            break;
                        case ComponentTypeWrapper.Processor:
                            break;
                        case ComponentTypeWrapper.OperatingSystem:
                            break;
                        case ComponentTypeWrapper.BuildTool:
                            break;
                        case ComponentTypeWrapper.ISA:
                            break;
                        case ComponentTypeWrapper.BuildParameter:
                            break;
                        case ComponentTypeWrapper.LibraryCategory:
                            LibraryCategoryWrapper libcat = PK.Wrapper.FindLibraryCategory(comp.Guid);
                            if (libcat != null)
                            {
                                this.OnSelectionChangeEvent(libcat);
                            }
                            break;
                        case ComponentTypeWrapper.Unknown:
                            break;
                        default:
                            break;
                    }
                }
            }
        }

        private void designer1_MouseUp(object sender, MouseEventArgs e)
        {
            if (designer1.Document.SelectedElements.Count == 1)
            {
                if (designer1.Document.SelectedElements[0].GetType() == typeof(MFRectangleNode))
                {
                    analizeReferencesToolStripMenuItem.Visible = true;
                    showPropertiesToolStripMenuItem.Visible = true;
                    //editToolStripMenuItem.Visible = true;
                    toolStripSeparator1.Visible = true;
                    toolStripSeparator2.Visible = true;
                }
                else
                {
                    analizeReferencesToolStripMenuItem.Visible = false;
                    showPropertiesToolStripMenuItem.Visible = false;
                    //editToolStripMenuItem.Visible = false;
                    toolStripSeparator1.Visible = false;
                    toolStripSeparator2.Visible = false;
                }
            }
            else
            {
                analizeReferencesToolStripMenuItem.Visible = false;
                showPropertiesToolStripMenuItem.Visible = false;
                //editToolStripMenuItem.Visible = false;
                toolStripSeparator1.Visible = false;
                toolStripSeparator2.Visible = false;
            }
        }

        private void designer1_ElementResizing(object sender, ElementEventArgs e)
        {
            if (designer1.Document.SelectedElements[0].GetType() == typeof(MFRectangleNode))
            {
                MFRectangleNode rn = (MFRectangleNode)e.Element;
                rn.Label.Location = rn.Location;
                rn.Label.Size = rn.Size;
            }
        }

        private void showPropertiesToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (designer1.Document.SelectedElements.Count == 1)
            {
                if (designer1.Document.SelectedElements[0].GetType() == typeof(MFRectangleNode))
                {
                    MFRectangleNode RectNode = (MFRectangleNode)designer1.Document.SelectedElements[0];
                    ComponentWrapper comp = (ComponentWrapper)RectNode.Tag;

                    switch (comp.ComponentType)
                    {
                        case ComponentTypeWrapper.Library:
                            LibraryWrapper lib = PK.Wrapper.FindLibrary(comp.Guid);
                            if (lib != null)
                            {
                                this.OnShowPropertiesEvent(lib);
                            }
                            break;
                        case ComponentTypeWrapper.Feature:
                            FeatureWrapper feat = PK.Wrapper.FindFeature(comp.Guid);
                            if (feat != null)
                            {
                                this.OnShowPropertiesEvent(feat);
                            }
                            break;
                        case ComponentTypeWrapper.MFAssembly:
                            break;
                        case ComponentTypeWrapper.MFSolution:
                            break;
                        case ComponentTypeWrapper.Processor:
                            break;
                        case ComponentTypeWrapper.OperatingSystem:
                            break;
                        case ComponentTypeWrapper.BuildTool:
                            break;
                        case ComponentTypeWrapper.ISA:
                            break;
                        case ComponentTypeWrapper.BuildParameter:
                            break;
                        case ComponentTypeWrapper.LibraryCategory:
                            LibraryCategoryWrapper libcat = PK.Wrapper.FindLibraryCategory(comp.Guid);
                            if (libcat != null)
                            {
                                this.OnShowPropertiesEvent(libcat);
                            }
                            break;
                        case ComponentTypeWrapper.Unknown:
                            break;
                        default:
                            break;
                    }
                }
            }
        }

        private void editToolStripMenuItem_Click(object sender, EventArgs e)
        {
            EditElement();

        }

        private void analizeReferencesToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (designer1.Document.SelectedElements.Count == 1)
            {
                if (designer1.Document.SelectedElements[0].GetType() == typeof(MFRectangleNode))
                {
                    MFRectangleNode RectNode = (MFRectangleNode)designer1.Document.SelectedElements[0];
                    ComponentWrapper comp = (ComponentWrapper)RectNode.Tag;
                    collection.AnalyseComponent(comp);
                    Visualize(collection);
                }
            }
        }

        private void designer1_KeyDown(object sender, KeyEventArgs e)
        {
            this.CtrlPressed = e.Control;
        }

        private void designer1_KeyUp(object sender, KeyEventArgs e)
        {
            this.CtrlPressed = e.Control;
        }

        private void designer1_MouseDoubleClick(object sender, MouseEventArgs e)
        {
            EditElement();
        }


        private void EditElement()
        {
            if (designer1.Document.SelectedElements.Count == 1)
            {
                if (designer1.Document.SelectedElements[0].GetType() == typeof(MFRectangleNode))
                {
                    MFRectangleNode RectNode = (MFRectangleNode)designer1.Document.SelectedElements[0];
                    ComponentWrapper comp = (ComponentWrapper)RectNode.Tag;
                    this.OnEditEvent(comp);
                }
            }
        }

        private void containingFolderToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (designer1.Document.SelectedElements.Count == 1)
            {
                if (designer1.Document.SelectedElements[0].GetType() == typeof(MFRectangleNode))
                {
                    MFRectangleNode RectNode = (MFRectangleNode)designer1.Document.SelectedElements[0];
                    ComponentWrapper comp = (ComponentWrapper)RectNode.Tag;

                    string path = string.Empty;

                    switch (comp.ComponentType)
                    {
                        case ComponentTypeWrapper.Library:
                            path = PK.Wrapper.FindLibrary(comp).ProjectPath;
                            break;
                        case ComponentTypeWrapper.Feature:
                            path = PK.Wrapper.FindFeature(comp.Guid).ProjectPath;
                            break;
                        case ComponentTypeWrapper.MFAssembly:
                            path = PK.Wrapper.FindAssembly(comp.Guid).ProjectPath;
                            break;
                        case ComponentTypeWrapper.MFSolution:
                            path = comp.ProjectPath;
                            break;
                        case ComponentTypeWrapper.Processor:
                            path = PK.Wrapper.FindProcessor(comp.Guid).ProjectPath;
                            break;
                        case ComponentTypeWrapper.OperatingSystem:
                            path = comp.ProjectPath;
                            break;
                        case ComponentTypeWrapper.BuildTool:
                            path = comp.ProjectPath;
                            break;
                        case ComponentTypeWrapper.ISA:
                            path = PK.Wrapper.FindISA(comp.Guid).InnerProjectPath;
                            break;
                        case ComponentTypeWrapper.BuildParameter:
                            path = comp.ProjectPath;
                            break;
                        case ComponentTypeWrapper.LibraryCategory:
                            path = PK.Wrapper.FindLibraryCategory(comp.Guid).ProjectPath;
                            break;
                        default:
                            path = comp.ProjectPath;
                            break;
                    }

                    this.OnOpenContainingFolderEvent(path);
                }
            }
        }

    }
}

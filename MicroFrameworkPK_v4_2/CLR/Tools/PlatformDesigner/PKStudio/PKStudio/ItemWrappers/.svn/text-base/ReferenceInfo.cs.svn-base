using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Collections;
using System.Diagnostics;
using System.Collections.ObjectModel;
using PKStudio.Tree.Nodes;
using System.Windows.Forms;
using XsdInventoryFormatObject;

namespace PKStudio.ItemWrappers
{

    public class ReferenceData
    {
        public Collection<ComponentWrapper> RequiredBy { get; private set; }
        public Collection<ComponentWrapper> Realization { get; private set; }
        public Collection<ComponentWrapper> DependsFrom { get; private set; }
        public BaseWrapper Wrapper { get; private set; }
        public ReferenceData(BaseWrapper Wrapper)
        {
            this.RequiredBy = new Collection<ComponentWrapper>();
            this.DependsFrom = new Collection<ComponentWrapper>();
            this.Realization = new Collection<ComponentWrapper>();
            this.Wrapper = Wrapper;
        }
        public void Clear()
        {
            this.RequiredBy.Clear();
            this.DependsFrom.Clear();
            this.Realization.Clear();
        }
    }

    public delegate bool OnAddComponentHandler(ComponentWrapper component, ReferenceInfo info);

    public abstract class ReferenceInfo : IEnumerable<ReferenceData>
    {
        protected Dictionary<string, ComponentWrapper> guidToInfoHash = new Dictionary<string, ComponentWrapper>();
        public Dictionary<ComponentWrapper, ReferenceData> References { get; protected set; }
        protected List<ComponentWrapper> ReadOnlyComponents { get; set; }
        protected ProjectWrapper Project { get; set; }
        protected SolutionWrapper Solution { get; set; } 

        protected abstract void CheckComponents();
        protected virtual void OnCalcReferences() {}

        protected abstract void OnComponentRefs(ComponentWrapper component);
        public abstract bool OnCheckComponent(ComponentWrapper component);
        protected abstract bool OnAddNode(BaseWrapper wrapper);
        public OnAddComponentHandler OnAddComponent { get; set; }
        public Collection<ComponentWrapper> AddedComponents { get; private set; }
        public Collection<ComponentWrapper> RemovedComponents { get; private set; }

        protected abstract CollectionWrapper<ComponentWrapper, MFComponent> Components { get; }

        public static bool AddComponentDefault(ComponentWrapper component, ReferenceInfo info)
        {
            return true;
        }

        public Collection<ComponentWrapper> CheckedComponents 
        {
            get
            {
                Collection<ComponentWrapper> collection = new Collection<ComponentWrapper>();
                foreach (ComponentWrapper component in this.AddedComponents)
                {
                    collection.Add(component);
                }
                foreach (ComponentWrapper component in this.Components)
                {
                    if (this.RemovedComponents.Contains(component) == false)
                        collection.Add(component);
                }
                return collection;
            }
        }


        private static BaseWrapper[] GetComponents()
        {
            List<BaseWrapper> components = new List<BaseWrapper>();
            foreach (FeatureWrapper feature in PK.Wrapper.GetFeatures())
            {
                components.Add(feature);
            }
            foreach (LibraryWrapper library in PK.Wrapper.GetLibraries())
            {
                components.Add(library);
            }
            foreach (LibraryCategoryWrapper libcat in PK.Wrapper.GetLibraryCategories())
            {
                components.Add(libcat);
            }
            return components.ToArray();
        }

        public ReferenceInfo(ProjectWrapper Project, SolutionWrapper Solution, OnAddComponentHandler OnAddComponent)
            : this(null, Project, Solution, OnAddComponent)
        {
        }
        
        public ReferenceInfo(Dictionary<ComponentWrapper, ReferenceData> references, ProjectWrapper Project, SolutionWrapper Solution, OnAddComponentHandler OnAddComponent)
        {
            this.ReadOnlyComponents = new List<ComponentWrapper>();
            this.Project = Project;
            this.Solution = Solution;
            this.OnAddComponent = OnAddComponent;
            this.AddedComponents = new Collection<ComponentWrapper>();
            this.RemovedComponents = new Collection<ComponentWrapper>();

            if (references != null)
            {
                this.References = references;
            }
            else
            {
                this.References = new Dictionary<ComponentWrapper, ReferenceData>();

                foreach (BaseWrapper wrapper in GetComponents())
                {
                    ComponentWrapper component = ComponentWrapper.GetComponentWrapper(wrapper);
                    References.Add(component, new ReferenceData(wrapper));
                }
                foreach (ComponentWrapper component in this.References.Keys)
                {
                    BaseWrapper wrapper = this[component].Wrapper;
                    switch (component.ComponentType)
                    {
                        case ComponentTypeWrapper.Library:
                            LibraryWrapper library = wrapper as LibraryWrapper;
                            Debug.Assert(library != null);
                            library.Dependencies = GetComponents(library.Dependencies);
                            if ((library.LibraryCategory != null) && (library.HasLibraryCategory))
                            {
                                library.LibraryCategory = GetComponent(library.LibraryCategory);
                            }
                            break;
                        case ComponentTypeWrapper.Feature:
                            FeatureWrapper feature = wrapper as FeatureWrapper;
                            Debug.Assert(feature != null);
                            feature.FeatureDependencies = GetComponents(feature.FeatureDependencies);
                            feature.ComponentDependencies = GetComponents(feature.ComponentDependencies);
                            break;
                        case ComponentTypeWrapper.LibraryCategory:
                            LibraryCategoryWrapper libcat = wrapper as LibraryCategoryWrapper;
                            Debug.Assert(libcat != null);
                            libcat.FeatureAssociations = GetComponents(libcat.FeatureAssociations);
                            break;
                        default:
                            Debug.Assert(false);
                            break;
                    }
                }
                this.Solution.TransportType.FeatureAssociations = GetComponents(this.Solution.TransportType.FeatureAssociations);
            }
        }

        
        protected void CheckComponent(ComponentWrapper component)
        {
            if (component.Checked)
            {
                this.ExchangeComponent(component, this.RemovedComponents, this.AddedComponents);
            }
            else
            {
                this.ExchangeComponent(component, this.AddedComponents, this.RemovedComponents);
            }
        }

        private void ExchangeComponent(ComponentWrapper component, Collection<ComponentWrapper> a, Collection<ComponentWrapper> b)
        {
            if (a.Contains(component) == false)
            {
                if (b.Contains(component) == false)
                {
                    b.Add(component);
                }
            }
            else
            {
                a.Remove(component);
            }
        }

        protected bool IsTransport(LibraryCategoryWrapper libcat)
        {
            return (libcat.IsTransport && this.Solution.TransportType.Equals(libcat));
        }

        protected void AddReadonly(ComponentWrapper component)
        {
            if (this.ReadOnlyComponents.Contains(component) == false)
                this.ReadOnlyComponents.Add(component);
            if (component.ComponentType == ComponentTypeWrapper.Feature)
            {
                if (this.Project.IsClrProject)
                {
                    if (this.Project.Features.Contains(component) == false)
                        this.Project.Features.Add(component);
                }
            }
        }

        public void CalcReferences()
        {
            this.ReadOnlyComponents.Clear();
            foreach (ComponentWrapper component in this.References.Keys)
            {
                ReferenceData refData = this[component];
                refData.Clear();
                component.Checked = false;
                if (component.ComponentType == ComponentTypeWrapper.Feature)
                {
                    FeatureWrapper feature = refData.Wrapper as FeatureWrapper;
                    Debug.Assert(feature != null);
                    if (feature != null)
                    {
                        if (feature.Required)
                        {
                            component.Checked = true;
                            AddReadonly(component);
                        }
                    }
                }
            }

            LibraryCategoryWrapper transport = this.Solution.TransportType;
            if (transport != null)
            {
                foreach (ComponentWrapper component in transport.FeatureAssociations)
                {
                    component.Checked = true;
                    AddReadonly(component);
                }
            }

            this.OnCalcReferences();

            foreach (ComponentWrapper component in this.References.Keys)
            {                
                this.OnComponentRefs(component);
            }
            this.CheckComponents();
        }

        public Collection<ComponentNode> GetNodes()
        {
            Collection<ComponentNode> nodes = new Collection<ComponentNode>();
            foreach (ComponentWrapper component in this.References.Keys)
            {
                if (this.OnAddComponent(component, this))
                    nodes.Add(new ComponentRealizationNode(component, null, this, OnAddNode));
            }
            return nodes;
        }

        public Collection<ComponentNode> GetRequiredBy(ComponentWrapper component)
        {
            ReferenceData refData = this[component];
            Collection<ComponentNode> nodes = new Collection<ComponentNode>();
            foreach (ComponentWrapper reference in refData.RequiredBy)
            {
                nodes.Add(new ComponentNode(reference, null));
            }
            return nodes;
        }

        public Collection<ComponentNode> GetDependsFrom(ComponentWrapper component)
        {
            ReferenceData refData = this[component];
            Collection<ComponentNode> nodes = new Collection<ComponentNode>();
            foreach (ComponentWrapper reference in refData.DependsFrom)
            {
                nodes.Add(new ComponentNode(reference, null));
            }
            return nodes;
        }

        private ComponentWrapper FindComponent(string guid)
        {
            ComponentWrapper result = null;
            guid = guid.ToUpper();
            if (guidToInfoHash.TryGetValue(guid, out result) == false)
            {
                foreach (ComponentWrapper item in this.References.Keys)
                {
                    if (item.IsSameGuid(guid))
                    {
                        guidToInfoHash.Add(item.Guid.ToUpper(), item);
                        result = item;
                        break;
                    }
                }
            }
            return result;
        }

        protected enum ReferenceType
        {
            Dependency,
            Realization,
            Assotiation
        }

        protected void MutualReference(ComponentWrapper component, ComponentWrapper dependency)
        {
            MutualReference(component, dependency, ReferenceType.Dependency);
        }

        protected void MutualReference(ComponentWrapper component, ComponentWrapper dependency, ReferenceType type)
        {
            ReferenceData thisReference = this.References[component];
            if (type == ReferenceType.Realization)
            {
                if (!thisReference.Realization.Contains(dependency))
                    thisReference.Realization.Add(dependency);
            }
            else
            {
                if (!thisReference.DependsFrom.Contains(dependency))
                    thisReference.DependsFrom.Add(dependency);
            }
            ReferenceData dependReference = this.References[dependency];
            if (type == ReferenceType.Realization)
            {
                if (!dependReference.Realization.Contains(component))
                    dependReference.Realization.Add(component);
            }
            else
            {
                if (type == ReferenceType.Dependency)
                {
                    if (!dependReference.RequiredBy.Contains(component))
                        dependReference.RequiredBy.Add(component);
                }
            }
        }

        protected ComponentWrapper GetComponent(ComponentWrapper component)
        {
            ComponentWrapper rescomponent = this.FindComponent(component.Guid);
            if (rescomponent != null)
            {
                ComponentWrapper.Copy(rescomponent, component);
            }
            return rescomponent;
        }

        protected CollectionWrapper<ComponentWrapper, MFComponent> GetComponents(CollectionWrapper<ComponentWrapper, MFComponent> components)
        {
            Collection<ComponentWrapper> result = new Collection<ComponentWrapper>();
            foreach (ComponentWrapper component in components)
            {
                ComponentWrapper rescomponent = this.FindComponent(component.Guid);
                if (rescomponent != null)
                {
                    ComponentWrapper.Copy(rescomponent, component);
                    result.Add(rescomponent);
                }
            }
            return result;
        }

        public ReferenceData this[ComponentWrapper component]
        {
            get
            {
                return this.References[component];
            }
        }

        public ReferenceData this[string guid]
        {
            get
            {
                ComponentWrapper component = this.FindComponent(guid);
                if (component != null)
                {
                    return this[component];
                }
                else
                    return null;
            }
        }


        public bool RecursiveCheckComponent(ComponentWrapper component)
        {
            ReferenceData refData = this[component];
            this.CheckComponent(component);
            bool recurcive = OnCheckComponent(component);
            if (component.Checked == true)
            {
                foreach (ComponentWrapper dependComponent in refData.DependsFrom)
                {
                    if (dependComponent.Checked == false)
                    {
                        dependComponent.Checked = true;
                        RecursiveCheckComponent(dependComponent);
                        recurcive = true;
                    }
                }
            }
            else
            {
                foreach (ComponentWrapper dependComponent in refData.RequiredBy)
                {
                    if (dependComponent.Checked == true)
                    {
                        dependComponent.Checked = false;
                        RecursiveCheckComponent(dependComponent);
                        recurcive = true;
                    }
                }
            }
            return recurcive;
        }

        public void GetRefList(ComponentWrapper component, out List<ComponentWrapper> refList)
        {
            refList = new List<ComponentWrapper>();
            ReferenceData refData = this.References[component];
            foreach (ComponentWrapper item in refData.RequiredBy)
            {
                if (item.Checked)
                {
                    refList.Add(item);
                }
            }
        }

        public bool IsFeatureReadOnly(ComponentWrapper component)
        {
            return this.ReadOnlyComponents.Contains(component);
        }


        public IEnumerator<ReferenceData> GetEnumerator()
        {
            foreach (ReferenceData item in this.References.Values)
            {
                yield return item;
            }
        }

        IEnumerator IEnumerable.GetEnumerator()
        {
            return this.GetEnumerator();
        }

    }

    public class FeatureReferenceInfo : ReferenceInfo
    {
        public FeatureReferenceInfo(ProjectWrapper Project, SolutionWrapper Solution)
            : base(Project, Solution,DefaultComponents)
        {
            Project.Features = GetComponents(Project.Features);
        }
        protected override void OnComponentRefs(ComponentWrapper component)
        {
            ReferenceData refData = this.References[component];
            FeatureWrapper feature = refData.Wrapper as FeatureWrapper;
            if (feature != null)
            {
                foreach (ComponentWrapper dependency in feature.FeatureDependencies)
                {
                    MutualReference(component, dependency);
                }
            }
        }

        private static bool DefaultComponents(ComponentWrapper component, ReferenceInfo info)
        {
            return (component.ComponentType == ComponentTypeWrapper.Feature);
        }


        protected override CollectionWrapper<ComponentWrapper, MFComponent> Components
        {
            get 
            {
                return this.Project.Features;
            }
        }

        public override bool OnCheckComponent(ComponentWrapper component)
        {
            return false;
        }


        protected override void CheckComponents()
        {
            foreach (ComponentWrapper feature in this.CheckedComponents)
            {
                feature.Checked = true;
            }
        }

        protected override bool OnAddNode(BaseWrapper wrapper)
        {
            return true;
        }
    }


    public class LibrariesInfo : ReferenceInfo
    {
        protected ProcessorWrapper Processor { get; private set; }
        protected FeatureReferenceInfo FeaturesInfo { get; set; }
        protected Collection<LibraryWrapper> Templates { get; set; }


        public LibrariesInfo(ProjectWrapper Project, SolutionWrapper Solution, FeatureReferenceInfo FeaturesInfo)
            : base(FeaturesInfo == null ? null : FeaturesInfo.References, Project, Solution, AllComponents)
        {
            this.Project.Libraries = GetComponents(this.Project.Libraries);
            this.Project.LibraryCategories = GetComponents(this.Project.LibraryCategories);
            this.Project.Features = GetComponents(this.Project.Features);
            this.Processor = PK.Wrapper.FindProcessor(Solution.Processor.Guid);
            this.Templates = new Collection<LibraryWrapper>();
            this.FeaturesInfo = FeaturesInfo;
        }

        protected Collection<ComponentWrapper> AddedFeatures 
        {
            get
            {
                return this.FeaturesInfo.AddedComponents;
            }
        }
        protected Collection<ComponentWrapper> RemovedFeatures
        {
            get
            {
                return this.FeaturesInfo.RemovedComponents;
            }
        }

        protected override CollectionWrapper<ComponentWrapper, MFComponent> Components
        {
            get 
            {  
                return this.Project.Libraries;
            }
        }

        private static bool DefaultComponents(ComponentWrapper component, ReferenceInfo info)
        {
            return (component.ComponentType == ComponentTypeWrapper.LibraryCategory);
        }
        
        public static bool AllComponents(ComponentWrapper component, ReferenceInfo info)
        {
            if (!DefaultComponents(component, info))
                return false;
            return component.Checked;
        }
        
        public static bool UnresolvedComponents(ComponentWrapper component, ReferenceInfo info)
        {
            if (!DefaultComponents(component, info))
                return false;
            bool result = false;
            if (component.Checked)
            {
                result = true;
                ReferenceData refData = info[component];
                foreach (ComponentWrapper library in refData.Realization)
                {
                    if (library.ComponentType == ComponentTypeWrapper.Library)
                    {
                        if (library.Checked)
                        {
                            result = false;
                            break;
                        }
                    }
                }
            }
            return result;
        }

        private bool ValidateLibrary(LibraryWrapper library)
        {
            if (((library.ProcessorSpecific != null) && !string.IsNullOrEmpty(library.ProcessorSpecific.Guid)) && (string.Compare(library.ProcessorSpecific.Guid, this.Solution.Processor.Guid, true) != 0))
            {
                return false;
            }
            if (!string.IsNullOrEmpty(library.CustomFilter))
            {
                bool found = false;
                //CustomFilter содержит список процессоров через разделитель ';'
                //Идем вдоль процессоров библиотеки
                foreach (string libfilter in library.CustomFilter.Split(new char[] { ';' }))
                {
                    //Идем вдоль процессоров процессора
                    foreach (string procfilter in this.Processor.CustomFilter.Split(new char[] { ';' }))
                    {
                        //Если найдено соответствие, то найдено
                        if (string.Compare(procfilter, libfilter, true) == 0)
                        {
                            found = true;
                            break;
                        }
                    }
                    //Если соответствия не найдено
                    if (found == false)
                    {
                        //Ищем в процессорах решения
                        foreach (string solutionfilter in this.Solution.CustomFilter.Split(new char[] { ';' }))
                        {
                            if (string.Compare(solutionfilter, libfilter, true) == 0)
                            {
                                found = true;
                                break;
                            }
                        }
                    }
                    //Если не найдено
                    if (found == false)
                    {
                        //Находим проект CLR
                        Collection<ComponentWrapper> features = null;
                        if (this.Project.IsClrProject)
                        {
                            features = this.FeaturesInfo.CheckedComponents;
                        }
                        else
                        {
                            foreach (ProjectWrapper project in this.Solution.Projects)
                            {
                                if (project.IsClrProject)
                                {
                                    features = GetComponents(project.Features);
                                    break;
                                }
                            }
                        }
                        if (features != null)
                        {
                            //Идем вдоль фич проекта CLR
                            foreach (ComponentWrapper component in features)
                            {
                                //Находим соответствующую фичу
                                FeatureWrapper feature = this[component].Wrapper as FeatureWrapper;
                                //И проверяем ее фильтр, если совпало, устанавливаем флаг
                                if ((feature != null) && (string.Compare(feature.Filter, libfilter, true) == 0))
                                {
                                    found = true;
                                    break;
                                }
                            }
                        }
                    }
                    //Если не найдено, в конечном итоге сравниваем с именем решения
                    if (!found)
                    {
                        found = 0 == string.Compare(library.CustomFilter, this.Solution.Name, true);
                    }
                    //Если найдено хоть одно соответствие выходим
                    if (found)
                    {
                        break;
                    }
                }
                if (!found)
                {
                    return false;
                }
            }
            //Если проект не Загрузчик а библиотека - загрузчик, то валидация не проходит
            if (!this.Project.IsBootloaderProject() && library.IsBootloaderLibrary())
            {
                return false;
            }
            //Есби библиотека - CLR а проект - нет, то валидация не проходит
            if ((library.Level == LibraryLevelWrapper.CLR) && !this.Project.IsClrProject)
            {
                return false;
            }
            string libProjectPath = library.ProjectPath.ToLower();
            //Если библиотека лежит в примерах, то валидация не проходит
            if (libProjectPath.Contains(@"\devicecode\drivers\sample\"))
            {
                return false;
            }
            //Если библиотека находится в другом проекте, то валидация не проходит
            if (libProjectPath.Contains(@"\solutions\") && !libProjectPath.Contains(@"\solutions\" + this.Solution.Name.ToLower() + @"\"))
            {
                return false;
            }

            return true;
        }


        bool IsUnresolved(ReferenceData refData)
        {
            LibraryCategoryWrapper libcat = refData.Wrapper as LibraryCategoryWrapper;
            Debug.Assert(libcat != null);
            if (libcat != null)
            {
                foreach (ComponentWrapper realization in refData.Realization)
                {
                    if (realization.Checked)
                    {
                        return false;
                    }
                }
            }
            return true;
        }


        ComponentWrapper GetAutoselectLibrary(ComponentWrapper component)
        {
            Debug.Assert(component.ComponentType == ComponentTypeWrapper.LibraryCategory);
            ReferenceData refData = this[component];
            LibraryCategoryWrapper libcat = refData.Wrapper as LibraryCategoryWrapper;
            Debug.Assert(libcat != null);
            ComponentWrapper defaultLib = null;
            ComponentWrapper stubLib = null;
            ComponentWrapper templateLib = null;
            ComponentWrapper bootloaderLib = null;
            ComponentWrapper projectLib = null;
            LibraryWrapper defaultWrapper = null;
            bool alterLib = false;

            foreach (ComponentWrapper library in refData.Realization)
            {
                LibraryWrapper wrapper = this[library].Wrapper as LibraryWrapper;
                Debug.Assert(wrapper != null);
                if (wrapper != null)
                {
                    if (this.Project.Libraries.Contains(library))
                    {
                        if (wrapper.IsStub == false)
                        {
                            projectLib = library;
                        }
                        else
                        {
                            stubLib = library;
                        }
                    }
                    if (wrapper.IsStub)
                    {
                        if (stubLib == null)
                            stubLib = library;
                    }
                    else if (wrapper.IsBootloaderLibrary())
                    {
                        bootloaderLib = library;
                    }
                    else if (wrapper.IsTemplate)
                    {
                        templateLib = library;
                    }
                    else if (defaultLib == null)
                    {
                        defaultLib = library;
                        defaultWrapper = wrapper;
                    }
                    else
                    {
                        alterLib = true;
                    }
                }
            }

            if (libcat != null)
            {
                if (libcat.FeatureAssociations.Count != 0)
                {
                    bool selected = false;
                    foreach (ComponentWrapper feature in libcat.FeatureAssociations)
                    {
                        if (feature.Checked == true)
                        {
                            selected = true;
                            break;
                        }
                    }
                    if (selected)
                    {
                        if (this.Project.IsBootloaderProject() == false)
                        {
                            if ((alterLib == false) && (defaultLib != null))
                            {
                                return defaultLib;
                            }
                            if (projectLib != null)
                            {
                                return projectLib;
                            }
                        }
                        else if (bootloaderLib == null)
                        {
                            if (this.IsTransport(libcat))
                            {
                                if (alterLib == false)
                                {
                                    return defaultLib;
                                }
                                if (stubLib != null)
                                {
                                    return stubLib;
                                }
                                if (((alterLib == true) || (defaultLib == null)) || (((templateLib != null) && (string.IsNullOrEmpty(defaultWrapper.CustomFilter))) && ((defaultWrapper.ProcessorSpecific != null) && (string.IsNullOrEmpty(defaultWrapper.ProcessorSpecific.Guid)))))
                                {
                                    return null;
                                }
                                return defaultLib;
                            }
                        }
                        else
                        {
                            return bootloaderLib;
                        }

                    }
                    else
                    {
                        if (this.IsTransport(libcat))
                        {
                            return null;
                        }
                        return stubLib;
                    }
                }
                else
                {
                    if (!this.Project.IsBootloaderProject())
                    {
                        if ((alterLib == false) && (defaultLib != null))
                        {
                            if ((stubLib == null) && (templateLib == null))
                            {
                                return defaultLib;
                            }
                            if (!string.IsNullOrEmpty(defaultWrapper.CustomFilter) || ((defaultWrapper.ProcessorSpecific != null) && (!string.IsNullOrEmpty(defaultWrapper.ProcessorSpecific.Guid))))
                            {
                                return defaultLib;
                            }
                        }
                        if (projectLib != null)
                        {
                            return projectLib;
                        }
                        if ((stubLib != null) && (this.Project.Libraries.Contains(stubLib)))
                        {
                            return stubLib;
                        }
                    }
                    else if (bootloaderLib == null)
                    {
                        if (stubLib != null)
                        {
                            return stubLib;
                        }
                        if (alterLib == false)
                        {
                            return defaultLib;
                        }
                    }
                    else 
                        return bootloaderLib;
                }
            }
            return null;
        }

        protected override void OnCalcReferences()
        {
            Collection<ComponentWrapper> templateList = new Collection<ComponentWrapper>();
            foreach (ComponentWrapper component in this.References.Keys)
            {
                LibraryWrapper template = this[component].Wrapper as LibraryWrapper;
                if ((template != null) && (template.IsTemplate))
                {
                    templateList.Add(component);
                }
            }
            foreach (ComponentWrapper component in templateList)
            {
                this.References.Remove(component);
            }
            this.Templates.Clear();
        }

        protected override void CheckComponents()
        {
            if (this.FeaturesInfo != null)
            {
                foreach (ComponentWrapper feature in this.FeaturesInfo.CheckedComponents)
                {
                    feature.Checked = true;
                }
            }

            foreach (LibraryWrapper template in this.Templates)
            {
                ComponentWrapper component = ComponentWrapper.GetComponentWrapper(template);
                this.References.Add(component, new ReferenceData(template));
                MutualReference(template.LibraryCategory, component, ReferenceType.Realization);
            }

            foreach (ComponentWrapper component in this.References.Keys)
            {
                ReferenceData refData = this[component];
                bool add = component.Checked;
                switch (component.ComponentType)
                {
                    case ComponentTypeWrapper.LibraryCategory:
                        LibraryCategoryWrapper libcat = refData.Wrapper as LibraryCategoryWrapper;
                        Debug.Assert(libcat != null);
                        if ((libcat.Required == true) || (this.IsTransport(libcat)))
                            add = true;
                        break;
                    case ComponentTypeWrapper.Library:
                        LibraryWrapper library = refData.Wrapper as LibraryWrapper;
                        if (library.IsTemplate)
                            component.Name = "Generate Template";
                        Debug.Assert(library != null);
                        if (library.Required == true)
                        {
                            component.Checked = true;
                            add = true;
                        }
                        break;
                    case ComponentTypeWrapper.Feature:
                        FeatureWrapper feature = refData.Wrapper as FeatureWrapper;
                        Debug.Assert(feature != null);
                        if (feature.Required == true)
                        {
                            component.Checked = true;
                            add = true;
                        }
                        break;
                    default:
                        Debug.Assert(false);
                        break;
                }
                if (add)
                    RecursiveAddComponent(component);
            }


            foreach (ComponentWrapper component in this.References.Keys)
            {
                if (DefaultComponents(component, this))
                    this.ReadOnlyComponents.Add(component);
                break;
            }
        }

        private void UnResolveLibraryCategory(ReferenceData refData, bool IsStub)
        {
            foreach (ComponentWrapper realization in refData.Realization)
            {
                if (realization.Checked)
                {
                    LibraryWrapper realizationlib = this[realization].Wrapper as LibraryWrapper;
                    Debug.Assert(realizationlib != null);
                    if (realizationlib != null)
                    {
                        if (realizationlib.IsStub == IsStub)
                        {
                            realization.Checked = false;
                            RecursiveCheckComponent(realization);
                        }
                    }
                    break;
                }
            }
        }

        private bool RecursiveAddComponent(ComponentWrapper component)
        {
            bool recursive = false;
            ReferenceData refData = this[component];
            if (component.ComponentType == ComponentTypeWrapper.LibraryCategory)
            {
                LibraryCategoryWrapper libcat = refData.Wrapper as LibraryCategoryWrapper;
                if ((component.Checked == false) && ((libcat.Level != LibraryLevelWrapper.CLR) || ((libcat.Level == LibraryLevelWrapper.CLR) && this.Project.IsClrProject)))
                {
                    component.Checked = true;
                    Debug.Assert(libcat != null);
                    bool unStub = libcat.Required;
                    bool isStub = true;
                    if (this.FeaturesInfo != null)
                    {
                        foreach (ComponentWrapper requirment in refData.RequiredBy)
                        {
                            if (requirment.ComponentType == ComponentTypeWrapper.Feature)
                            {
                                if (this.AddedFeatures.Contains(requirment))
                                {
                                    unStub = true;
                                    break;
                                }
                                if (libcat.Required == false)
                                {
                                    if (this.RemovedFeatures.Contains(requirment))
                                    {
                                        unStub = true;
                                        isStub = false;
                                        break;
                                    }
                                }
                            }
                        }
                        if (libcat != null)
                        {
                            foreach (ComponentWrapper assotiation in libcat.FeatureAssociations)
                            {
                                if (assotiation.ComponentType == ComponentTypeWrapper.Feature)
                                {
                                    if (this.AddedFeatures.Contains(assotiation))
                                    {
                                        unStub = true;
                                        break;
                                    }
                                    if (libcat.Required == false)
                                    {
                                        if (this.RemovedFeatures.Contains(assotiation))
                                        {
                                            unStub = true;
                                            isStub = false;
                                            break;
                                        }
                                    }
                                }
                            }
                        }
                    }
                    if (unStub == true)
                    {
                        UnResolveLibraryCategory(refData, isStub);
                    }

                    if (IsUnresolved(refData))
                    {
                        ComponentWrapper autoselect = GetAutoselectLibrary(component);
                        if (autoselect != null)
                        {
                            Debug.Assert(autoselect.ComponentType == ComponentTypeWrapper.Library);
                            autoselect.Checked = true;
                            recursive |= RecursiveCheckComponent(autoselect);
                        }
                    }
                }
            }
            if (component.Checked == true)
            {
                foreach (ComponentWrapper dependency in refData.DependsFrom)
                {
                    switch (dependency.ComponentType)
                    {
                        case ComponentTypeWrapper.Feature:
                        case ComponentTypeWrapper.LibraryCategory:
                        case ComponentTypeWrapper.Library:
                            RecursiveAddComponent(dependency);
                            recursive = true;
                            break;
                    }
                }
            }
            return recursive;
        }

        protected override bool OnAddNode(BaseWrapper wrapper)
        {
            ComponentWrapper component = wrapper as ComponentWrapper;
            if (component != null)
            {
                switch (component.ComponentType)
                {
                    case ComponentTypeWrapper.Feature:
                    case ComponentTypeWrapper.Library:
                    case ComponentTypeWrapper.LibraryCategory:
                        return true;
                }
            }
            return false;
        }

        public override bool OnCheckComponent(ComponentWrapper component)
        {
            bool recursive = false;
            ReferenceData refData = this[component];
            if (refData.Wrapper is LibraryWrapper)
            {
                if (component.Checked)
                {
                    foreach (ComponentWrapper libcat in refData.Realization)
                    {
                        ReferenceData libcatRefData = this[libcat];
                        foreach (ComponentWrapper library in libcatRefData.Realization)
                        {
                            if ((library.Equals(component) == false) && (library.Checked))
                            {
                                library.Checked = false;
                                recursive |= RecursiveCheckComponent(library);
                            }
                        }
                    }
                }
                recursive |= RecursiveAddComponent(component);
            }
            return recursive;
        }


        protected override void OnComponentRefs(ComponentWrapper component)
        {
            ReferenceData refData = this.References[component];
            switch (component.ComponentType)
            {
                case ComponentTypeWrapper.Feature:
                    FeatureWrapper feature = refData.Wrapper as FeatureWrapper;
                    Debug.Assert(feature != null);
                    if (feature != null)
                    {
                        foreach (ComponentWrapper dependency in feature.ComponentDependencies)
                        {
                            MutualReference(component, dependency);
                        }
                    }
                    break;
                case ComponentTypeWrapper.Library:
                    LibraryWrapper library = refData.Wrapper as LibraryWrapper;
                    Debug.Assert(library != null);
                    if (library != null)
                    {
                        if ((library.LibraryCategory != null) && (library.HasLibraryCategory == true))
                        {
                            if (this.ValidateLibrary(library))
                                MutualReference(library.LibraryCategory, component, ReferenceType.Realization);
                        }
                        foreach (ComponentWrapper dependency in library.Dependencies)
                        {
                            MutualReference(component, dependency);
                        }
                    }
                    break;
                case ComponentTypeWrapper.LibraryCategory:
                    LibraryCategoryWrapper libcat = refData.Wrapper as LibraryCategoryWrapper;
                    Debug.Assert(libcat != null);
                    if (libcat != null)
                    {
                        //foreach (ComponentWrapper assotiation in libcat.FeatureAssociations)
                        //{
                        //    MutualReference(assotiation, component,ReferenceType.Assotiation);
                        //}

                        if ((libcat.Level != LibraryLevelWrapper.CLR) && (libcat.Templates.Count != 0))
                        {
                            LibraryWrapper template = PK.Wrapper.CreateLibrary(
                                libcat.Name + "_" + this.Solution.Name,
                                libcat.Level,
                                @"Generates template code in your solution's DeviceCode directory for the given Library Category.The project will be generated in Solutions\" + this.Solution.Name + @"\DeviceCode\" + libcat.Name,
                                PK.Wrapper.SpoClientPath + @"Solutions\" + this.Solution.Name + @"\DeviceCode\" + libcat.Name + @"\dotnetmf.proj",
                                true,
                                component);
                            this.Templates.Add(template);
                        }
                    }
                    break;
            }
        }
    }

}

using System;
using System.Collections.Generic;
using System.ComponentModel;
using PKStudio.ItemWrappers.Converters;
using XsdInventoryFormatObject;
using System.Collections.ObjectModel;
using PKStudio.Tree.Nodes;
using System.Collections;

namespace PKStudio.ItemWrappers
{

    public class FeatureReferenceEnumerator : IEnumerable<ComponentWrapper>
    {
        private FeatureWrapper This { get; set; }
        private bool OnlyChecked { get; set; }

        public FeatureReferenceEnumerator(FeatureWrapper This, bool onlyChecked)
        {
            this.This = This;
            this.OnlyChecked = onlyChecked;
        }

        public FeatureReferenceEnumerator(FeatureWrapper This)
            : this(This, false)
        {
        }

        public IEnumerator<ComponentWrapper> GetEnumerator()
        {
            foreach (FeatureWrapper feature in PK.Wrapper.GetFeatures())
            {
                if (feature.Equals(This))
                    continue;
                foreach (ComponentWrapper dependComp in feature.FeatureDependencies)
                {
                    if (dependComp.IsSameGuid(This))
                    {
                        ComponentWrapper component = ComponentWrapper.GetComponentWrapper(feature);
                        if ((this.OnlyChecked == true) && (component.Checked == false))
                            continue;
                        yield return component;
                    }
                }
            }
        }

        IEnumerator IEnumerable.GetEnumerator()
        {
            return this.GetEnumerator();
        }
    }


    [Serializable]
    public class FeatureWrapper : BaseTypedWrapper<Feature>, IGroups, IGuid, IName, IProjectPath, IDescription, IDocumentation, IFilter
    {

        public CollectionWrapper<ComponentWrapper, MFComponent> ReferencedBy(bool onlyChecked)
        {
            return Wrap<CollectionWrapper<ComponentWrapper, MFComponent>>(new FeatureReferenceEnumerator(this, onlyChecked));//new CollectionWrapper<ComponentWrapper, MFComponent>(new FeatureReferenceEnumerator(this, onlyChecked));
        }

        private FeatureWrapper(Feature feature)
            : base(feature)
        {
        }

        protected override BaseNode OnGetTreeNode(BaseNode parent)
        {
            return new FeatureNode(this, parent);
        }


        [Category("General")]
        [TypeConverter(typeof(ExpandableCollectionConverter<ComponentWrapper, MFComponent>))]
        public CollectionWrapper<ComponentWrapper, MFComponent> Assemblies
        {
            get
            {
                return WrapList<ComponentWrapper, MFComponent>(this.InnerObject.Assemblies);
                //return this.InnerObject.Assemblies;
            }
            set
            {
                //this.InnerObject.Assemblies = value;
            }
        }

        [Category("General")]
        [TypeConverter(typeof(ExpandableCollectionConverter<ComponentWrapper, MFComponent>))]
        public CollectionWrapper<ComponentWrapper, MFComponent> ComponentDependencies
        {
            get
            {
                return WrapList<ComponentWrapper, MFComponent>(this.InnerObject.ComponentDependencies);
                //return this.InnerObject.ComponentDependencies;
            }
            set
            {
                //this.InnerObject.ComponentDependencies = value;
                this.InnerObject.ComponentDependencies = UnWrapList<ComponentWrapper, MFComponent>(value);
            }
        }

        [Category("General")]
        public string Description
        {
            get
            {
                return this.InnerObject.Description;
            }
            set
            {
                this.InnerObject.Description = value;
            }
        }

        [Category("General")]
        public string Documentation
        {
            get
            {
                return this.InnerObject.Documentation;
            }
            set
            {
                this.InnerObject.Documentation = value;
            }
        }

        [Category("General")]
        [TypeConverter(typeof(ExpandableCollectionConverter<ComponentWrapper, MFComponent>))]
        public CollectionWrapper<ComponentWrapper, MFComponent> FeatureDependencies
        {
            get
            {
                return WrapList<ComponentWrapper, MFComponent>(this.InnerObject.FeatureDependencies);
                //return this.InnerObject.FeatureDependencies;
            }
            set
            {
                this.InnerObject.FeatureDependencies = UnWrapList<ComponentWrapper, MFComponent>( value);
            }
        }

        [Category("General")]
        public string Filter
        {
            get
            {
                return this.InnerObject.Filter;
            }
            set
            {
                this.InnerObject.Filter = value;
            }
        }

        [Category("General")]
        public string Groups
        {
            get
            {
                return this.InnerObject.Groups;
            }
            set
            {
                this.InnerObject.Groups = value;
            }
        }

        [Category("General")]
        public string Guid
        {
            get
            {
                return this.InnerObject.Guid;
            }
            set
            {
                this.InnerObject.Guid = value;
            }
        }

        [Category("General")]
        public bool Hidden
        {
            get
            {
                return this.InnerObject.Hidden;
            }
            set
            {
                this.InnerObject.Hidden = value;
            }
        }

        [Category("General")]
        public bool IsSolutionWizardVisible
        {
            get
            {
                return this.InnerObject.IsSolutionWizardVisible;
            }
            set
            {
                this.InnerObject.IsSolutionWizardVisible = value;
            }
        }

        [Category("General")]
        public string Name
        {
            get
            {
                return this.InnerObject.Name;
            }
            set
            {
                this.InnerObject.Name = value;
            }
        }

        [Category("General")]
        public string ProjectPath
        {
            get
            {
                return this.InnerObject.ProjectPath;
            }
            set
            {
                this.InnerObject.ProjectPath = value;
            }
        }

        [Category("General")]
        public bool Required
        {
            get
            {
                return this.InnerObject.Required;
            }
            set
            {
                this.InnerObject.Required = value;
            }
        }
    }
}

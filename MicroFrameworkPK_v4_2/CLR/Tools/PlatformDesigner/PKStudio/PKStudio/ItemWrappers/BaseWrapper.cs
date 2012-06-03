using System;
using System.Collections;
using System.Collections.Generic;
using System.ComponentModel;
using System.Diagnostics;
using System.Linq;
using System.Reflection;
using System.Text.RegularExpressions;
using PKStudio.Tree.Nodes;
using System.Collections.ObjectModel;
using XsdInventoryFormatObject;

namespace PKStudio.ItemWrappers
{
    [Serializable]
    public abstract class BaseWrapper : INotifyPropertyChanged
    {
        protected BaseWrapper()
        {
        }

        private static WeakCache _cache = new WeakCache();

        public BaseNode GetTreeNode(BaseNode parent)
        {
            BaseNode node = OnGetTreeNode(parent);
            this.PropertyChanged += new PropertyChangedEventHandler(node.OnPropertyChanged);
            return node;
        }

        protected abstract BaseNode OnGetTreeNode(BaseNode parent);


        public static W Wrap<W>(object obj)
        {
            return _cache.Wrap<W>(obj);
        }

        private class WrapperFilterCollection<T> : IEnumerable
        {
            public IEnumerator GetEnumerator()
            {
                foreach (object item in _cache)
                {
                    if (item is T)
                        yield return item;
                }
            }
        }
       
        private class WrapperCollection<T> : IEnumerable
        {
            IEnumerable Collection { get; set; }
            public WrapperCollection()
            {
                this.Collection = new WrapperFilterCollection<T>();
            }
            public IEnumerator GetEnumerator()
            {
                foreach (object item in this.Collection)
                {
                    if (typeof(T).IsInterface)
                    {
                        if (!item.GetType().GetInterfaces().Contains(typeof(T)))
                            continue;
                    }
                    yield return item;
                }
            }
        }

        public static I[] GetCollectionOf<I>()
        {
            List<I> list = new List<I>();
            foreach (I item in new WrapperCollection<I>())
            {
                list.Add(item);
            }
            return list.ToArray();
        }

        [Browsable(false)]
        public virtual string InnerName 
        {
            get
            {
                IName name = this as IName;
                if (name != null)
                {
                    return name.Name;
                }
                else
                    return string.Empty;
            }
            set
            {
                IName name = this as IName;
                if (name != null)
                {
                    name.Name = value;
                }
            }
        }

        [Browsable(false)]
        public virtual string InnerGroups
        {
            get
            {
                IGroups group = this as IGroups;
                if (group != null)
                {
                    return group.Groups;
                }
                else
                    return string.Empty;
            }
            set
            {
                IGroups group = this as IGroups;
                if (group != null)
                {
                    group.Groups = value;
                }
            }
        }

        [Browsable(false)]
        public virtual string InnerGuid
        {
            get
            {
                IGuid guid = this as IGuid;
                if (guid != null)
                {
                    return guid.Guid;
                }
                else
                    return string.Empty;
            }
            set
            {
                IGuid guid = this as IGuid;
                if (guid != null)
                {
                    guid.Guid = value;
                }
            }
        }

        [Browsable(false)]
        public virtual VersionWrapper InnerVersion
        {
            get
            {
                IVersion version = this as IVersion;
                if (version != null)
                {
                    return version.Version;
                }
                else
                    return null;
            }
            set
            {
                IVersion version = this as IVersion;
                if (version != null)
                {
                    version.Version = value;
                }
            }
        }

        [Browsable(false)]
        public virtual bool InnerChecked
        {
            get
            {
                IChecked check = this as IChecked;
                if (check != null)
                {
                    return check.Checked;
                }
                else
                    return false;
            }
            set
            {
                IChecked check = this as IChecked;
                if (check != null)
                {
                    check.Checked = value;
                }
            }
        }

        [Browsable(false)]
        public virtual string InnerProjectPath
        {
            get
            {
                IProjectPath projectPath = this as IProjectPath;
                if (projectPath != null)
                {
                    return projectPath.ProjectPath;
                }
                else
                    return string.Empty;
            }
            set
            {
                IProjectPath projectPath = this as IProjectPath;
                if (projectPath != null)
                {
                    projectPath.ProjectPath = value;
                }
            }
        }

        [Browsable(false)]
        public virtual string InnerConditional
        {
            get
            {
                IConditional conditional = this as IConditional;
                if (conditional != null)
                {
                    return conditional.Conditional;
                }
                else
                    return string.Empty;
            }
            set
            {
                IConditional conditional = this as IConditional;
                if (conditional != null)
                {
                    conditional.Conditional = value;
                }
            }
        }

        [Browsable(false)]
        public virtual string DetailDescription
        {
            get
            {
                IDetailDescription detaildescription = this as IDetailDescription;
                if (detaildescription != null)
                {
                    return detaildescription.DetailDescription;
                }
                else
                    return string.Empty;
            }
        }

        [Browsable(false)]
        public virtual string InnerDescription
        {
            get
            {
                IDescription description = this as IDescription;
                if (description != null)
                {
                    return description.Description;
                }
                else
                    return string.Empty;
            }
            set
            {
                IDescription description = this as IDescription;
                if (description != null)
                {
                    description.Description = value;
                }
            }
        }

        [Browsable(false)]
        public virtual string InnerDocumentation
        {
            get
            {
                IDocumentation documentation = this as IDocumentation;
                if (documentation != null)
                {
                    return documentation.Documentation;
                }
                else
                    return string.Empty;
            }
            set
            {
                IDocumentation documentation = this as IDocumentation;
                if (documentation != null)
                {
                    documentation.Documentation = value;
                }
            }
        }

        [Browsable(false)]
        public virtual CollectionWrapper<ComponentWrapper, MFComponent> InnerDependencies
        {
            get
            {
                IDependencies documentation = this as IDependencies;
                if (documentation != null)
                {
                    return documentation.Dependencies;
                }
                else
                    return new CollectionWrapper<ComponentWrapper,MFComponent>(new List<ComponentWrapper>());
            }
            set
            {
                IDependencies documentation = this as IDependencies;
                if (documentation != null)
                {
                    documentation.Dependencies = value;
                }
            }
        }

        [Browsable(false)]
        public virtual string InnerFilter
        {
            get
            {
                IFilter filter = this as IFilter;
                if (filter != null)
                {
                    return filter.Filter;
                }
                else
                    return string.Empty;
            }
            set
            {
                IFilter filter = this as IFilter;
                if (filter != null)
                {
                    filter.Filter = value;
                }
            }
        }

        [Browsable(false)]
        public abstract string ClassName { get; }

        public static CollectionWrapper<W, L> WrapList<W, L>(List<L> list)
             where W : BaseTypedWrapper<L>
        {
            if (list == null)
                return null;
            return Wrap<CollectionWrapper<W, L>>(list);//new CollectionWrapper<W, L>(list);
        }
        public static List<L> UnWrapList<W, L>(CollectionWrapper<W, L> list)
            where W : BaseTypedWrapper<L>
        {
            if (list == null)
                return null;
            List<L> value = new List<L>();
            foreach (W item in list)
            {
                value.Add(item.InnerObject);
            }
            return value;
        }
        public static W[] WrapArray<W, L>(L[] list)
             where W : BaseTypedWrapper<L>
        {
            return Wrap<CollectionWrapper<W, L>>(list).ToArray();//WrapList<W, L>(new List<L>(list)).ToArray();
        }

        public event PropertyChangedEventHandler PropertyChanged;

        protected void OnPropertyChange(string property)
        {
            if (this.PropertyChanged != null)
            {
                this.PropertyChanged(this, new PropertyChangedEventArgs(property));
            }
        }
    }

    [Serializable]
    public abstract class BaseTypedWrapper<T> : BaseWrapper
    {
       
        protected override BaseNode OnGetTreeNode(BaseNode parent)
        {
            Debug.Assert(false);
            throw new NotImplementedException();
        }

        protected BaseTypedWrapper(T InnerObject)
        {
            this.InnerObject = InnerObject;
        }

        private string innerObjectName;
        [Browsable(false)]
        public T InnerObject {get; private set;}

        [Browsable(false)]
        public override string ClassName 
        {
            get
            {
                if (innerObjectName == null)
                {
                    this.innerObjectName = this.InnerObject.GetType().ToString();
                    Match m = Regex.Match(this.innerObjectName, "(?<class>[^.]*$)");
                    if (m.Success)
                    {
                        this.innerObjectName = m.Groups["class"].Value;
                    }
                }
                return this.innerObjectName;
            }
        }

    }

    public interface IChecked
    {
        bool Checked { get; set; }
    }

    public interface IGroups
    {
        string Groups { get; set; }
    }

    public interface IGuid
    {
        string Guid { get; set; }
    }

    public interface IName
    {
        string Name { get; set; }
    }

    public interface IVersion
    {
        VersionWrapper Version { get; set; }
    }

    public interface IConditional
    {
        string Conditional { get; set; }
    }

    public interface IProjectPath
    {
        string ProjectPath { get; set; }
    }

    public interface IDetailDescription
    {
        string DetailDescription { get; }
    }

    public interface IDescription
    {
        string Description { get; set; }
    }

    public interface IDocumentation
    {
        string Documentation { get; set; }
    }

    public interface IDependencies
    {
        CollectionWrapper<ComponentWrapper, MFComponent> Dependencies { get; set; }
    }

    public interface IFilter
    {
        string Filter { get; set; }
    }
}

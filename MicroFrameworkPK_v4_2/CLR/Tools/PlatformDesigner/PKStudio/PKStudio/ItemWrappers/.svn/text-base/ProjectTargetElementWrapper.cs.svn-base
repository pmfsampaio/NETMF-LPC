using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Microsoft.Build.Construction;
using System.ComponentModel;

namespace PKStudio.ItemWrappers
{
    [DefaultProperty("Name"), Serializable]
    public class ProjectTargetElementWrapper : BaseTypedWrapper<ProjectTargetElement>
    {
        private ProjectTargetElementWrapper(ProjectTargetElement element)
            : base(element)
        {
        }
        // Summary:
        //     Gets or sets the AfterTargets attribute value.
        //
        // Returns:
        //     Returns the AfterTargets attribute value. Returns an empty string if the
        //     attribute is not present.
        [Category("General")]
        public string AfterTargets { get { return this.InnerObject.AfterTargets; } set { value = this.InnerObject.AfterTargets; } }
        //
        // Summary:
        //     Gets or sets the BeforeTargets attribute value.
        //
        // Returns:
        //     Returns the BeforeTargets attribute value. Returns an empty string if the
        //     attribute is not present.
        [Category("General")]
        public string BeforeTargets { get { return this.InnerObject.BeforeTargets; } set { value = this.InnerObject.BeforeTargets; } }
        //
        // Summary:
        //     Gets or sets the DependsOnTargets attribute value. Returns empty string if
        //     it is not present. Removes the attribute if the value to set is empty.
        //
        // Returns:
        //     Returns the DependsOnTargets attribute value. Returns an empty string if
        //     the attribute is not present.
        [Category("General")]
        public string DependsOnTargets { get { return this.InnerObject.DependsOnTargets; } set { value = this.InnerObject.DependsOnTargets; } }
        //
        // Summary:
        //     Gets or sets the Inputs attribute value. Returns empty string if it is not
        //     present. Removes the attribute if the value to set is empty.
        //
        // Returns:
        //     Returns the Inputs attribute value. Returns an empty string if the attribute
        //     is not present.
        [Category("General")]
        public string Inputs { get { return this.InnerObject.Inputs; } set { value = this.InnerObject.Inputs; } }
        //
        // Summary:
        //     Gets all child item groups
        //
        // Returns:
        //     Returns all child item groups.
        [Category("General")]
        public ICollection<ProjectItemGroupElement> ItemGroups { get { return this.InnerObject.ItemGroups; } }
        //
        // Summary:
        //     Gets or sets the TrimDuplicateOutputs attribute value.
        //
        // Returns:
        //     Returns the TrimDuplicateOutputs attribute value. Returns an empty string
        //     if the attribute is not present.
        [Category("General")]
        public string KeepDuplicateOutputs { get { return this.InnerObject.KeepDuplicateOutputs; } set { value = this.InnerObject.KeepDuplicateOutputs; } }
        //
        // Summary:
        //     Gets and sets the name of the this target.
        //
        // Returns:
        //     Returns the name of the this target.
        [Category("General")]
        public string Name { get { return this.InnerObject.Name; } set { value = this.InnerObject.Name; } }
        //
        // Summary:
        //     Get all child OnError Element (MSBuild).
        //
        // Returns:
        //     Returns all child OnError elements.
        [Category("General")]
        public ICollection<ProjectOnErrorElement> OnErrors { get { return this.InnerObject.OnErrors; } }
        //
        // Summary:
        //     Gets or sets the Outputs attribute value. Returns empty string if it is not
        //     present. Removes the attribute if the value to set is empty.
        //
        // Returns:
        //     Returns the Outputs attribute value. Returns an empty string if the attribute
        //     is not present.
        [Category("General")]
        public string Outputs { get { return this.InnerObject.Outputs; } set { value = this.InnerObject.Outputs; } }
        //
        // Summary:
        //     Gets all child property groups.
        //
        // Returns:
        //     Returns all child property groups.
        [Category("General")]
        public ICollection<ProjectPropertyGroupElement> PropertyGroups { get { return this.InnerObject.PropertyGroups; } }
        //
        // Summary:
        //     Gets or sets the Returns attribute value.
        //
        // Returns:
        //     Returns the returns attribute value; null if the attribute is not present
        [Category("General")]
        public string Returns { get { return this.InnerObject.Returns; } set { value = this.InnerObject.Returns; } }
        //
        // Summary:
        //     Gets all child tasks.
        //
        // Returns:
        //     Returns all child tasks.
        [Category("General")]
        public ICollection<ProjectTaskElement> Tasks { get { return this.InnerObject.Tasks; } }
    }
}

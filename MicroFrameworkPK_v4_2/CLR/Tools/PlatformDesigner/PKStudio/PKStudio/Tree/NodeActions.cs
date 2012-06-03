using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace PKStudio.Tree
{
 
    public enum NodeAction
    {       
        Properties,
        Edit,
        New,
        References,
        Exclude,
        Remove,
        Manage,
        OpenFolder,
        Build,
        Rebuild
    }

    public class NodeEventArgs : EventArgs
    {
        public NodeAction Action { get; private set; }
        public NodeEventArgs(NodeAction action)
        {
            this.Action = action;
        }
        public static NodeEventArgs Edit
        {
            get
            {
                return new NodeEventArgs(NodeAction.Edit);
            }
        }
        public static NodeEventArgs New
        {
            get
            {
                return new NodeEventArgs(NodeAction.New);
            }
        }
        public static NodeEventArgs Manage
        {
            get
            {
                return new NodeEventArgs(NodeAction.Manage);
            }
        }
        public static NodeEventArgs Properties
        {
            get
            {
                return new NodeEventArgs(NodeAction.Properties);
            }
        }
        public static NodeEventArgs References
        {
            get
            {
                return new NodeEventArgs(NodeAction.References);
            }
        }
        public static NodeEventArgs Remove
        {
            get
            {
                return new NodeEventArgs(NodeAction.Remove);
            }
        }
        public static NodeEventArgs Exclude
        {
            get
            {
                return new NodeEventArgs(NodeAction.Exclude);
            }
        }
        public static NodeEventArgs OpenFolder
        {
            get
            {
                return new NodeEventArgs(NodeAction.OpenFolder);
            }
        }
        public static NodeEventArgs Build
        {
            get
            {
                return new NodeEventArgs(NodeAction.Build);
            }
        }
        public static NodeEventArgs Rebuild
        {
            get
            {
                return new NodeEventArgs(NodeAction.Rebuild);
            }
        }

    }
}

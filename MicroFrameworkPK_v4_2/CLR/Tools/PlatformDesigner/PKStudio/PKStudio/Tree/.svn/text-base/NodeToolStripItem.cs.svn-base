using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Drawing;

namespace PKStudio.Tree
{
    public class NodeToolStripMenuItem : ToolStripMenuItem
    {
        public NodeToolStripMenuItem(string text, Image image, EventHandler onClick, EventArgs args)
            : base(text, image, onClick)
        {
            this.Arg = args;
        }
        public NodeToolStripMenuItem(string text, Image image, EventHandler onClick)
            : this(text, image, onClick, EventArgs.Empty)
        {
        }

        public EventArgs Arg { get; set; }

        protected override void OnClick(EventArgs e)
        {
            base.OnClick(this.Arg);
        }

        public static ToolStripMenuItem GetMIProjectNew(EventHandler onClick)
        {
            return new NodeToolStripMenuItem(Resources.IDS_TREE_MENU_ITEM_NEW_PROJECT, Resources.ProjectAdd, onClick, NodeEventArgs.New);
        }
        public static ToolStripMenuItem GetMIFeatureNew(EventHandler onClick)
        {
            return new NodeToolStripMenuItem(Resources.IDS_TREE_MENU_ITEM_NEW_FEATURE, Resources.FeatureAdd, onClick, NodeEventArgs.New);
        }
        public static ToolStripMenuItem GetMILibraryNew(EventHandler onClick)
        {
            return new NodeToolStripMenuItem(Resources.IDS_TREE_MENU_ITEM_NEW_LIBRARY, Resources.LibraryAdd, onClick, NodeEventArgs.New);
        }
        public static ToolStripMenuItem GetMILibraryCategoryNew(EventHandler onClick)
        {
            return new NodeToolStripMenuItem(Resources.IDS_TREE_MENU_ITEM_NEW_LIBRARY_CATEGORY, Resources.LibraryCategoryAdd, onClick, NodeEventArgs.New);
        }
        public static ToolStripMenuItem GetMIFileNew(EventHandler onClick)
        {
            return new NodeToolStripMenuItem(Resources.IDS_TREE_MENU_ITEM_NEW_FILE, Resources.FileAdd, onClick, NodeEventArgs.New);
        }
        public static ToolStripMenuItem GetMIProperties(EventHandler onClick)
        {
            return new NodeToolStripMenuItem(Resources.IDS_TREE_MENU_ITEM_PROPERTIES, Resources.Properties, onClick, NodeEventArgs.Properties);
        }
        public static ToolStripMenuItem GetMIEdit(EventHandler onClick)
        {
            return new NodeToolStripMenuItem(Resources.IDS_TREE_MENU_ITEM_EDIT, Resources.Edit, onClick, NodeEventArgs.Edit);
        }
        public static ToolStripMenuItem GetMIExclude(EventHandler onClick)
        {
            return new NodeToolStripMenuItem(Resources.IDS_TREE_MENU_ITEM_EXCLUDE, null, onClick, NodeEventArgs.Exclude);
        }
        public static ToolStripMenuItem GetMIRemove(EventHandler onClick)
        {
            return new NodeToolStripMenuItem(Resources.IDS_TREE_MENU_ITEM_REMOVE, Resources.Remove, onClick, NodeEventArgs.Remove);
        }
        public static ToolStripMenuItem GetMIManage(EventHandler onClick)
        {
            return new NodeToolStripMenuItem(Resources.IDS_TREE_MENU_ITEM_MANAGE, Resources.Manage, onClick, NodeEventArgs.Manage);
        }
        public static ToolStripMenuItem GetMIOpenFilder(EventHandler onClick)
        {
            return new NodeToolStripMenuItem(Resources.IDS_TREE_MENU_ITEM_OPEN_FOLDER, Resources.FolderOpened, onClick, NodeEventArgs.OpenFolder);
        }
        public static ToolStripMenuItem GetMIBuild(EventHandler onClick)
        {
            return new NodeToolStripMenuItem(Resources.IDS_TREE_MENU_ITEM_BUILD, null, onClick, NodeEventArgs.Build);
        }
        public static ToolStripMenuItem GetMIRebuild(EventHandler onClick)
        {
            return new NodeToolStripMenuItem(Resources.IDS_TREE_MENU_ITEM_REBUILD, null, onClick, NodeEventArgs.Rebuild);
        }

    }
}

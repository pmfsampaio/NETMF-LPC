using System.Collections.Generic;
using ComponentObjectModel;
using XsdInventoryFormatObject;
using System.Collections.ObjectModel;

namespace PKStudio.ItemWrappers
{
    public class InventoryHelperWrapper : BaseTypedWrapper<InventoryHelper>
    {
        public InventoryHelperWrapper(InventoryHelperWrapper helper)
            : base(helper.InnerObject)
        {
        }

        private static Inventory[] GetInvs(params InventoryWrapper[] inventories)
        {
            List<Inventory> invs = new List<Inventory>();
            foreach (InventoryWrapper inv in inventories)
            {
                invs.Add(inv.InnerObject);
            }
            return invs.ToArray();
        }

        public InventoryHelperWrapper(params InventoryWrapper[] inventories)
            : base(new InventoryHelper(GetInvs(inventories)))
        {
        }


        public InventoryWrapper DefaultInventory
        {
            get
            {
                return BaseWrapper.Wrap < InventoryWrapper >(this.InnerObject.DefaultInventory);
            }
        }
        public LibraryCategoryWrapper[] LibraryCategories
        {
            get
            {
                return WrapArray<LibraryCategoryWrapper, LibraryCategory>(this.InnerObject.LibraryCategories);
            }
        }
        public FeatureWrapper[] Features
        {
            get
            {
                return WrapArray<FeatureWrapper, Feature>(this.InnerObject.Features);
            }
        }
        public LibraryWrapper[] Libraries
        {
            get
            {
                return WrapArray<LibraryWrapper, Library>(this.InnerObject.Libraries);
            }
        }

        public ISAWrapper[] ISAs
        {
            get
            {
                return WrapArray<ISAWrapper, ISA>(this.InnerObject.ISAs);
            }
        }

        public AssemblyWrapper[] Assemblies
        {
            get
            {
                return WrapArray<AssemblyWrapper, MFAssembly>(this.InnerObject.Assemblies);
            }
        }

        public SolutionWrapper[] Solutions
        {
            get
            {
                return WrapArray<SolutionWrapper, MFSolution>(this.InnerObject.Solutions);
            }
        }

        public ProcessorWrapper[] Processors
        {
            get
            {
                return WrapArray<ProcessorWrapper, Processor>(this.InnerObject.Processors);
            }
        }

        public BuildToolWrapper_[] BuildTools
        {
            get
            {
                return WrapArray<BuildToolWrapper_, BuildTool>(this.InnerObject.BuildTools);
            }
        }

        public AssemblyWrapper FindAssembly(string asmGuid)
        {
            return BaseWrapper.Wrap<AssemblyWrapper>(this.InnerObject.FindAssembly(asmGuid));
        }

        public AssemblyWrapper FindAssemblyByName(string asmName)
        {
            return BaseWrapper.Wrap<AssemblyWrapper>(this.InnerObject.FindAssemblyByName(asmName));
        }

        public FeatureWrapper FindFeature(string featureGuid)
        {
            return BaseWrapper.Wrap<FeatureWrapper>(this.InnerObject.FindFeature(featureGuid));//new FeatureWrapper(this.InnerObject.FindFeature(featureGuid));
        }

        public FeatureWrapper FindFeatureByName(string name)
        {
            return BaseWrapper.Wrap<FeatureWrapper>(this.InnerObject.FindFeatureByName(name));
        }

        public FeatureWrapper FindFeatureByProject(string featProject)
        {
            return BaseWrapper.Wrap<FeatureWrapper>(this.InnerObject.FindFeatureByName(featProject));
        }

        public LibraryCategoryWrapper FindLibraryCategory(string LibraryCategoryGuid)
        {
            return BaseWrapper.Wrap<LibraryCategoryWrapper>(this.InnerObject.FindLibraryCategory(LibraryCategoryGuid));
        }

        public LibraryCategoryWrapper FindLibraryCategoryByName(string LibraryCategoryName)
        {
            return BaseWrapper.Wrap<LibraryCategoryWrapper>(this.InnerObject.FindLibraryCategoryByName(LibraryCategoryName));
        }

        public LibraryWrapper FindLibrary(string libraryGuid)
        {
            return BaseWrapper.Wrap<LibraryWrapper>(this.InnerObject.FindLibrary(libraryGuid));
        }

        public LibraryWrapper FindLibrary(ComponentWrapper comp)
        {
            return BaseWrapper.Wrap<LibraryWrapper>(this.InnerObject.FindLibrary(comp.InnerObject));
        }

        public LibraryWrapper FindLibraryByFile(string libraryFile)
        {
            return BaseWrapper.Wrap<LibraryWrapper>(this.InnerObject.FindLibraryByFile(libraryFile));
        }

        public LibraryWrapper FindLibraryByName(string libraryName)
        {
            return BaseWrapper.Wrap<LibraryWrapper>(this.InnerObject.FindLibraryByName(libraryName));
        }

        public LibraryWrapper FindLibraryByProject(string libraryProj)
        {
            return BaseWrapper.Wrap<LibraryWrapper>(this.InnerObject.FindLibraryByProject(libraryProj));
        }
        public ProcessorWrapper FindProcessor(string processorGuid)
        {
            return BaseWrapper.Wrap<ProcessorWrapper>(this.InnerObject.FindProcessor(processorGuid));
        }

        public ProcessorWrapper FindProcessorByName(string procName)
        {
            return BaseWrapper.Wrap<ProcessorWrapper>(this.InnerObject.FindProcessorByName(procName));
        }

        public ISAWrapper FindISA(string ISAGuid)
        {
            return BaseWrapper.Wrap<ISAWrapper>(this.InnerObject.FindISA(ISAGuid));
        }

        public FeatureWrapper[] GetRequiredFeatures()
        {
            return WrapArray<FeatureWrapper, Feature>(this.InnerObject.GetRequiredFeatures());
        }

        public LibraryWrapper[] GetRequiredLibraries()
        {
            return WrapArray<LibraryWrapper, Library>(this.InnerObject.GetRequiredLibraries());
        }

        public LibraryCategoryWrapper[] GetRequiredLibraryCategories()
        {
            return WrapArray<LibraryCategoryWrapper, LibraryCategory>(this.InnerObject.GetRequiredLibraryCategories());
        }

        public List<LibraryCategoryWrapper> GetTransports()
        {
            return new List<LibraryCategoryWrapper>(WrapList<LibraryCategoryWrapper, LibraryCategory>(this.InnerObject.GetTransports()));
        }
    }
}

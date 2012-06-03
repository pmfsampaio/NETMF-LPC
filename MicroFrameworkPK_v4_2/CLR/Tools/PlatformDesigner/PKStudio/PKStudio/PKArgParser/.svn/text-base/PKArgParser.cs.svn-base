using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Text.RegularExpressions;

namespace PKParser.Arg
{
    public class PKArgParser
    {
        protected const string PARAM = "param";
        protected const string ARGS = "args";
        protected const string FILE = "file";
        protected const string FILE_NAME = "filename";
        protected const string FILE_REGEX = @"(?<" + FILE + @">(?:(?:[a-zA-Z]:\\+)|\\+)?(?:[^\\/:*?""<>|\r\n\s]+\\+)*(?<" + FILE_NAME + @">[^\\/:*?""<>|\r\n\s]+)|""(?:(?:[a-zA-Z]:\\)|\\)?(?:[^\\/:*?""<>|\r\n]+\\+)*(?<" + FILE_NAME + @">[^\\/:*?""<>|\r\n]+)"")";

        public CmdCollection Result { get; private set; }
        public SortedList<int, ParamCollection> Files { get; private set; }

        public PKArgParser()
        {
            this.Result = new CmdCollection(string.Empty);
            //this.Files = new Dictionary<int, ParamCollection>();
            this.Files = new SortedList<int, ParamCollection>();
        }

        public void Clear()
        {
            this.Result.Clear();
            this.Files.Clear();
        }

        private abstract class StringParser
        {
            public string Name { get; private set; }
            public StringParser(string Name)
            {
                this.Name = Name;
            }

            abstract public string Pattern { get; }

            private ParamCollection Parse(ref string s, string pattern, bool remove, string tag, RegexOptions options)
            {
                ParamCollection cmd = new ParamCollection(Name);
                Regex rex = new Regex(pattern, options);
                Match m1 = rex.Match(s);
                while (m1.Success)
                {
                    string param = m1.Groups[PARAM].Value;
                    string arg = m1.Groups[ARGS].Value;
                    if (param != null)
                    {
                        param = param.TrimEnd(' ');
                        ArgCollection prm = cmd.Add(param, new ArgCollection(param, tag));
                        if (arg != null)
                        {
                            arg = arg.TrimEnd(' ');
                            if (!string.IsNullOrEmpty(arg))
                            {
                                prm.Add(arg);
                            }
                        }
                    }
                    if (remove)
                    {
                        s = s.Remove(m1.Index, m1.Length).Trim();
                        m1 = rex.Match(s);
                    }
                    else
                    {
                        m1 = rex.Match(s, m1.Index + m1.Length);
                    }
                }
                return cmd;
            }

            virtual public ParamCollection Parse(ref string s)
            {
                return Parse(ref s, this.Pattern, true, "options", RegexOptions.None);
            }

            virtual public ParamCollection Parse(ref string s, RegexOptions options)
            {
                return Parse(ref s, this.Pattern, true, "options", options);
            }

            protected string Match(ref Regex rex, ref ParamCollection result, ref Match m, string s, string group, string tag)
            {
                string file_name = m.Groups[group].Value.Trim();
                result.Add(file_name, new ArgCollection(file_name, tag));
                s = s.Remove(m.Index, m.Length).Trim();
                m = rex.Match(s);
                return s;
            }

        }

        private class ArmCCStringParser : StringParser
        {
            public List<string> Files { get; private set; }
            public ArmCCStringParser(string name)
                : base(name)
            {
            }


            public override string Pattern
            {
                get
                {
                    return @"(?:\s|\A)(?<param>--allow_null_this|--no_allow_this|--alternative_tokens|--no_alternative_tokens|--anachronisms|--no_anachronisms|--arm|--arm_only|--asm|--autoinline|--no_autoinline|--bigend|--bitband|--brief_diagnostics|--no_brief_diagnostics|-c|-C|--c90|--c99|--code_gen|--no_code_gen|--compile_all_input|--no_compile_all_input|--cpp|--data_reorder|--no_data_reorder|--debug|--no_debug|--debug_macros|--no_debug_macros|--dep_name|--no_dep_name|--depend_system_headers|--no_depend_system_headers|--dollar|--no_dollar|--dwarf2|--dwarf3|-E|--emit_frame_directives|--no_emit_frame_directives|--enum_is_int|--exceptions|--no_exceptions|--exceptions_unwind|--no_exceptions_unwind|--export_defs_implicitly|--no_export_defs_implicitly|--extended_initializers|--no_extended_initializers|--force_new_nothrow|--no_force_new_nothrow|--forceinline|--friend_injection|--no_friend_injection|-g|-gnu|--gnu_instrument|--no_gnu_instrument|--guiding_decls|--no_guiding_decls|--help|--hide_all|--no_hide_all|--ignore_missing_headers|--implicit_include|--no_implicit_include|--implicit_include_searches|--no_implicit_include_searches|--implicit_typename|--no_implicit_typename|--inline|--no_inline|--interface_enums_are_32_bit|--interleave|--kandr_include|--list|--list_macros|--littleend|--long_long|--loose_implicit_cast|--lower_ropi|--no_lower_ropi|--lower_rwpi|--no_lower_rwpi|--ltcg|-M|--md|--mm|--multibyte_chars|--no_multibyte_chars|--multifile|--no_multifile|--nonstd_qualifier_deduction|--no_nonstd_qualifier_deduction|--old_specializations|--no_old_specializations|--parse_templates|--no_parse_templates|--pch|--pch_messages|--no_pch_messages|--pch_verbose|--no_pch_verbose|--phony_targets|--preprocessed|--reduce_paths|--no_reduce_paths|--relaxed_ref_def|--no_relaxed_ref_def|--remarks|--remove_unneeded_entities|--no_remove_unneeded_entities|--restrict|--no_restrict|--rtti|--no_rtti|-S|--show_cmdline|--signed_bitfields|--unsigned_bitfields|--signed_chars|--unsigned_chars|--split_ldm|--split_sections|--strict|--no_strict|--strict_warnings|--sys_include|--thumb|--trigraphs|--no_trigraphs|--unaligned_access|--no_unaligned_access|--using_std|--no_using_std|--vfe|--no_vfe|--vla|--no_vla|--vsn|-W|--wchar|--no_wchar|--wchar16|--wchar32|--whole_program|--wrap_diagnostics|--no_wrap_diagnostics)\b|(?:\s|\A)(?<param>(?:--apcs))\s*=?\s*(?<args>(?:(?:(?:/?(?:interwork|nointerwork|ropi|noropi|nopic|pic|rwpi|norwpi|nopid|pid))(?:/(?:\b(?:interwork|nointerwork|ropi|noropi|nopic|pic|rwpi|norwpi|nopid|pid)\b))*)(?:\s*,\s*(?:(?:/?(?:interwork|nointerwork|ropi|noropi|nopic|pic|rwpi|norwpi|nopid|pid))(?:/(?:\b(?:interwork|nointerwork|ropi|noropi|nopic|pic|rwpi|norwpi|nopid|pid)\b))*))*))|(?:\s|\A)(?<param>(?:--bss_threshold))\s*=?\s*(?<args>\b(?:0|8)\b)|(?:\s|\A)(?<param>(?:--compatible|--device_opt))\s*=?\s*(?<args>\b\w+\b)|(?:\s|\A)(?<param>(?:--create_pch|--depend|--errors|--feedback|-o|--preinclude|--use_pch|--via))\s*=?\s*(?<args>(?:(?:[a-zA-Z]:\\\\?)|\\\\?)?(?:[^\\/:*""?<>|\r\n\s]+\\\\?)*(?:[^\\/:*?""<>|\r\n\s]+)|""(?:(?:[a-zA-Z]:\\\\?)|\\\\?)?(?:[^\\/:*?""<>|\r\n]+\\\\?)*(?:[^\\/:*?""<>|\r\n]+)"")|(?:\s|\A)(?<param>(?:-D|-U))\s*=?\s*(?<args>(?:[^(\s=""]+)(?:\([^)\s]+\))?(?:=[^""\s]+|=""[^""\\]*(?:\\.[^""\\]*)*"")?)|(?:\s|\A)(?<param>(?:--default_extension))\s*=?\s*(?<args>\b(?:[^\\/:*?""<>|\r\n]+)\b)|(?:\s|\A)(?<param>(?:--depend_target|--device|--fpu|--locale))\s*=?\s*(?<args>\b[a-zA-Z_][a-zA-Z0-9_]*\b)|(?:\s|\A)(?<param>(?:--diag_error|--diag_remark|--diag_suppress|--diag_warning))\s*=?\s*(?<args>(?:\b\w+\b(?:\s*,\s*\b\w+\b)*))|(?:\s|\A)(?<param>(?:--diag_style))\s*=?\s*(?<args>\b(?:arm|ide|gnu)\b)|(?:\s|\A)(?<param>(?:--fpmode))\s*=?\s*(?<args>\b(?:ieee_full|ieee_fixed|ieee_no_fenv|std|fast)\b)|(?:\s|\A)(?<param>(?:--global_reg))\s*=?\s*(?<args>(?:[1-8](?:\s*,\s*[1-8])*))|(?:\s|\A)(?<param>(?:--gnu_version))\s*=?\s*(?<args>\b[0-9]+\b)|(?:\s|\A)(?<param>(?:-I))\s*=?\s*(?<args>(?:(?:(?:[a-zA-Z]:\\\\?)|\\\\?)?(?:[^\\/:*""?<>|\r\n\s]+\\\\?)*(?:[^\\/:*?""<>|\r\n\s]+)|""(?:(?:[a-zA-Z]:\\\\?)|\\\\?)?(?:[^\\/:*?""<>|\r\n]+\\\\?)*(?:[^\\/:*?""<>|\r\n]+)""(?:\s*,\s*(?:(?:[a-zA-Z]:\\\\?)|\\\\?)?(?:[^\\/:*""?<>|\r\n\s]+\\\\?)*(?:[^\\/:*?""<>|\r\n\s]+)|""(?:(?:[a-zA-Z]:\\\\?)|\\\\?)?(?:[^\\/:*?""<>|\r\n]+\\\\?)*(?:[^\\/:*?""<>|\r\n]+)"")*))|(?:\s|\A)(?<param>(?:--info))\s*=?\s*(?<args>\b(?:totals)\b)|(?:\s|\A)(?<param>(?:-J|--pch_dir))\s*=?\s*(?<args>(?:(?:[a-zA-Z]:\\\\?)|\\\\?)?(?:[^\\/:*""?<>|\r\n\s]+\\\\?)*(?:[^\\/:*?""<>|\r\n\s]+)|""(?:(?:[a-zA-Z]:\\\\?)|\\\\?)?(?:[^\\/:*?""<>|\r\n]+\\\\?)*(?:[^\\/:*?""<>|\r\n]+)"")|(?:\s|\A)(?<param>(?:--library_interface))\s*=?\s*(?<args>\b(?:rvct|rvct_c90)\b)|(?:\s|\A)(?<param>(?:--library_type))\s*=?\s*(?<args>\b(?:standardlib|microlib)\b)|(?:\s|\A)(?<param>(?:--message_locale))\s*=?\s*(?<args>[a-zA-Z_][a-zA-Z0-9_]*(?:\.[a-zA-Z_][a-zA-Z0-9_]*)?)|(?:\s|\A)(?<param>(?:--min_array_alignment|--pointer_alignment))\s*=?\s*(?<args>\b(?:1|2|4|8)\b)|(?:\s|\A)(?<param>(?:--multiply_latency|--pending_instantiations))\s*=?\s*(?<args>\b(?:(?<!\S)\d+(?!\S)|0[xX][0-9a-fA-F]+)\b)|(?:\s|\A)(?<param>(?:-O))\s*=?\s*(?<args>(?:0|1|2|3)\b)|(?:\s|\A)(?<param>(?:-O))\s*=?\s*(?<args>(?:space|time)\b)|(?:\s|\A)(?<param>(?:--retain))\s*=?\s*(?<args>\b(?:fns|inlinefns|noninlinefns|paths|calls:distinct|calls|libcalls|data:order|data|rodata|rwdata)\b)";
                }
            }

            public override ParamCollection Parse(ref string s)
            {
                ParamCollection result = base.Parse(ref s);
                Regex file = new Regex(FILE_REGEX);
                Match m = file.Match(s);
                while (m.Success)
                {
                    result.Files.Add(result.Files.Count + 1, m.Groups[FILE].Value);
                    s = Match(ref file, ref result, ref m, s, FILE, "file_list");
                }
                return result;
            }
        }

        private class ArmASMStringParser : StringParser
        {
            public List<string> Files { get; private set; }
            public ArmASMStringParser(string name)
                : base(name)
            {
            }

            public override string Pattern
            {
                get
                {
                    return @"(?:\s|\A)(?<param>--16|--32|--arm|--arm_only|--bi|--bigend|--brief_diagnostics|--checkreglist|--cpreproc|--debug|--dwarf2|--dwarf3|--exceptions|--exceptions_unwind|-g|--keep|--length|--li|--littleend|-m|--md|--no_code_gen|--no_esc|--no_exceptions|--no_exceptions_unwind|--no_hide_all|--no_regs|--no_terse|--no_unaligned_access|--no_warn|--predefine|--reduce_paths|--no_reduce_paths|--show_cmdline|--split_ldm|--thumb|--unaligned_access|--unsafe|--untyped_local_labels|--width|--xref)\b|(?:\s|\A)(?<param>(?:--apcs))\s*=?\s*(?<args>(?:(?:(?:/?(?:none|interwork|nointerwork|inter|nointer|ropi|noropi|nopic|pic|rwpi|norwpi|nopid|pid))(?:/(?:\b(?:none|interwork|nointerwork|inter|nointer|ropi|noropi|nopic|pic|rwpi|norwpi|nopid|pid)\b))*)(?:\s*,\s*(?:(?:/?(?:none|interwork|nointerwork|inter|nointer|ropi|noropi|nopic|pic|rwpi|norwpi|nopid|pid))(?:/(?:\b(?:none|interwork|nointerwork|inter|nointer|ropi|noropi|nopic|pic|rwpi|norwpi|nopid|pid)\b))*))*))|(?:\s|\A)(?<param>(?:--compatible|--device|--fpu))\s*=?\s*(?<args>\b[a-zA-Z_][a-zA-Z0-9_]*\b)|(?:\s|\A)(?<param>(?:--depend|--errors|--list|-o|--via))\s*=?\s*(?<args>(?:(?:[a-zA-Z]:\\\\?)|\\\\?)?(?:[^\\/:*""?<>|\r\n\s]+\\\\?)*(?:[^\\/:*?""<>|\r\n\s]+)|""(?:(?:[a-zA-Z]:\\\\?)|\\\\?)?(?:[^\\/:*?""<>|\r\n]+\\\\?)*(?:[^\\/:*?""<>|\r\n]+)"")|(?:\s|\A)(?<param>(?:--depend_format))\s*=?\s*(?<args>\b(?:unix|unix_escaped|unix_quoted)\b)|(?:\s|\A)(?<param>(?:--device_opt))\s*=?\s*(?<args>\b\w+\b)|(?:\s|\A)(?<param>(?:--diag_error|--diag_remark|--diag_warning|--diag_suppress))\s*=?\s*(?<args>(?:\b\w+\b(?:\s*,\s*\b\w+\b)*))|(?:\s|\A)(?<param>(?:--diag_style))\s*=?\s*(?<args>\b(?:arm|ide|gnu)\b)|(?:\s|\A)(?<param>(?:--fpmode))\s*=?\s*(?<args>\b(?:ieee_full|ieee_fixed|ieee_no_fenv|std|fast)\b)|(?:\s|\A)(?<param>(?:-i))\s*=?\s*(?<args>(?:(?:(?:[a-zA-Z]:\\\\?)|\\\\?)?(?:[^\\/:*""?<>|\r\n\s]+\\\\?)*(?:[^\\/:*?""<>|\r\n\s]+)|""(?:(?:[a-zA-Z]:\\\\?)|\\\\?)?(?:[^\\/:*?""<>|\r\n]+\\\\?)*(?:[^\\/:*?""<>|\r\n]+)""(?:\s*,\s*(?:(?:[a-zA-Z]:\\\\?)|\\\\?)?(?:[^\\/:*""?<>|\r\n\s]+\\\\?)*(?:[^\\/:*?""<>|\r\n\s]+)|""(?:(?:[a-zA-Z]:\\\\?)|\\\\?)?(?:[^\\/:*?""<>|\r\n]+\\\\?)*(?:[^\\/:*?""<>|\r\n]+)"")*))|(?:\s|\A)(?<param>(?:--library_type))\s*=?\s*(?<args>\b(?:standardlib|microlib)\b)|(?:\s|\A)(?<param>(?:--maxcache))\s*=?\s*(?<args>\b(?:(?<!\S)\d+(?!\S)|0[xX][0-9a-fA-F]+)\b)|(?:\s|\A)(?<param>(?:--memaccess))\s*=?\s*(?<args>(?:\+L41|-L22|-S22|-L22-S22))|(?:\s|\A)(?<param>(?:--pd|--PD))\s*=?\s*(?<args>""[^""\\]*(?:\\.[^""\\]*)*"")|(?:\s|\A)(?<param>(?:--regnames))\s*=?\s*(?<args>\b(?:none|callstd|all)\b)";
                }
            }

            public override ParamCollection Parse(ref string s)
            {
                ParamCollection result = base.Parse(ref s, RegexOptions.IgnoreCase);
                Regex file = new Regex(FILE_REGEX);
                Match m = file.Match(s);
                while (m.Success)
                {
                    result.Files.Add(result.Files.Count + 1, m.Groups[FILE].Value);
                    s = Match(ref file, ref result, ref m, s, FILE, "file_list");
                }
                return result;
            }
        }

        private class ArmLINKStringParser : StringParser
        {
            public ArmLINKStringParser(string name)
                : base(name)
            {
            }

            public override string Pattern
            {
                get
                {
                    return @"(?:\s|\A)(?<param>--arm_only|--autoat|--no_autoat|--be8|--be32|--no_bestdebug|--bestdebug|--no_branchnop|--branchnop|--callgraph|--no_callgraph|--combreloc|--no_combreloc|--compress_debug|--no_compress_debug|--no_keep_init_arrays|--no_cppinit|--debug|--no_debug|--exceptions|--no_exceptions|--filtercomment|--no_filtercomment|--force_so_throw|--no_force_so_throw|--help|--inline|--no_inline|--inlineveneer|--no_inlineveneer|--largeregions|--no_largeregions|--legacyalign|--no_legacyalign|--list_mapping_symbols|--no_list_mapping_symbols|--locals|--no_locals|--ltcg|--mangled|--unmangled|--map|--no_map|--merge|--no_merge|--muldefweak|--no_muldefweak|--override_visibility|--partial|--piveneer|--no_piveneer|--privacy|--reduce_paths|--no_reduce_paths|--ref_cpp_init|--no_ref_cpp_init|--reloc|--remove|--no_remove|--ropi|--rosplit|--rwpi|--scanlib|--no_scanlib|--show_cmdline|--split|--no_startup|--strict|--strict_relocations|--no_strict_relocations|--symbols|--no_symbols|--tailreorder|--no_tailreorder|--veneershare|--no_veneershare|--verbose|--vsn|--xref|--no_xref|--xrefdbg|--no_xrefdbg)\b|(?:\s|\A)(?<param>(?:--callgraph_file|--errors|--feedback|--list|--output|--profile|--scatter|--symdefs|--via))\s*=?\s*(?<args>(?:(?:[a-zA-Z]:\\\\?)|\\\\?)?(?:[^\\/:*""?<>|\r\n\s]+\\\\?)*(?:[^\\/:*?""<>|\r\n\s]+)|""(?:(?:[a-zA-Z]:\\\\?)|\\\\?)?(?:[^\\/:*?""<>|\r\n]+\\\\?)*(?:[^\\/:*?""<>|\r\n]+)"")|(?:\s|\A)(?<param>(?:--callgraph_output))\s*=?\s*(?<args>\b(?:fmt|html|text)\b)|(?:\s|\A)(?<param>(?:--cgfile))\s*=?\s*(?<args>\b(?:all|user|system)\b)|(?:\s|\A)(?<param>(?:--cgsymbol))\s*=?\s*(?<args>\b(?:all|locals|globals)\b)|(?:\s|\A)(?<param>(?:--cgundefined))\s*=?\s*(?<args>\b(?:all|entries|calls|none)\b)|(?:\s|\A)(?<param>(?:--cppinit|--device|--entry|--fini|--fpu|--info_lib_prefix|--init|--startup|--unresolved))\s*=?\s*(?<args>\b[a-zA-Z_][a-zA-Z0-9_]*\b)|(?:\s|\A)(?<param>(?:--datacompressor))\s*=?\s*(?<args>\b(?:on|off|list|id)\b)|(?:\s|\A)(?<param>(?:--diag_error|--diag_remark|--diag_suppress|--diag_warning))\s*=?\s*(?<args>(?:\b\w+\b(?:\s*,\s*\b\w+\b)*))|(?:\s|\A)(?<param>(?:--diag_style))\s*=?\s*(?<args>\b(?:arm|ide|gnu)\b)|(?:\s|\A)(?<param>(?:--edit|--libpath|--userlibpath))\s*=?\s*(?<args>(?:(?:(?:[a-zA-Z]:\\\\?)|\\\\?)?(?:[^\\/:*""?<>|\r\n\s]+\\\\?)*(?:[^\\/:*?""<>|\r\n\s]+)|""(?:(?:[a-zA-Z]:\\\\?)|\\\\?)?(?:[^\\/:*?""<>|\r\n]+\\\\?)*(?:[^\\/:*?""<>|\r\n]+)""(?:\s*,\s*(?:(?:[a-zA-Z]:\\\\?)|\\\\?)?(?:[^\\/:*""?<>|\r\n\s]+\\\\?)*(?:[^\\/:*?""<>|\r\n\s]+)|""(?:(?:[a-zA-Z]:\\\\?)|\\\\?)?(?:[^\\/:*?""<>|\r\n]+\\\\?)*(?:[^\\/:*?""<>|\r\n]+)"")*))|(?:\s|\A)(?<param>(?:--exceptions_tables))\s*=?\s*(?<args>\b(?:nocreate|unwind|cantunwind)\b)|(?:\s|\A)(?<param>(?:--feedback_image))\s*=?\s*(?<args>\b(?:none|noerrors|simple|full)\b)|(?:\s|\A)(?<param>(?:--feedback_type))\s*=?\s*(?<args>\b(?:noiw|iw|nounused|unused)\b)|(?:\s|\A)(?<param>(?:--first|--keep|--last))\s*=?\s*(?<args>(?:[^\\/:""<>|\r\n\s(]+(?:\s*\(\s*[^\\/:""<>|\r\n]+\s*\))?))|(?:\s|\A)(?<param>(?:--info))\s*=?\s*(?<args>(?:\b(?:architecture|common|debug|exceptions|inline|inputs|libraries|merge|sizes|stack|summarysizes|summarystack|tailreorder|totals|unused|veneers|veneercallers|visibility)\b(?:\s*,\s*\b(?:architecture|common|debug|exceptions|inline|inputs|libraries|merge|sizes|stack|summarysizes|summarystack|tailreorder|totals|unused|veneers|veneercallers|visibility)\b)*))|(?:\s|\A)(?<param>(?:--library_type))\s*=?\s*(?<args>\b(?:standardlib|microlib)\b)|(?:\s|\A)(?<param>(?:--match))\s*=?\s*(?<args>\b(?:crossmangled)\b)|(?:\s|\A)(?<param>(?:--max_visibility))\s*=?\s*(?<args>\b(?:default|protected)\b)|(?:\s|\A)(?<param>(?:--pad))\s*=?\s*(?<args>\b0[xX][0-9a-fA-F]+\b)|(?:\s|\A)(?<param>(?:--predefine))\s*=?\s*(?<args>""[^""\\]*(?:\\.[^""\\]*)*"")|(?:\s|\A)(?<param>(?:--ro_base|--rw_base))\s*=?\s*(?<args>\b(?:(?<!\S)\d+(?!\S)|0[xX][0-9a-fA-F]+)\b)|(?:\s|\A)(?<param>(?:--section_index_display))\s*=?\s*(?<args>\b(?:internal|input)\b)|(?:\s|\A)(?<param>(?:--sort))\s*=?\s*(?<args>\b(?:List|Lexical|AvgCallDepth|CallTree|RunningDepth)\b)|(?:\s|\A)(?<param>(?:--vfemode))\s*=?\s*(?<args>\b(?:on|off|force|force_no_rtti)\b)|(?:\s|\A)(?<param>(?:--xreffrom|--xrefto))\s*=?\s*(?<args>[a-zA-Z_][a-zA-Z0-9_]*\([a-zA-Z_][a-zA-Z0-9_]*\))";
                }
            }
            public override ParamCollection Parse(ref string s)
            {
                ParamCollection result = base.Parse(ref s);
                Regex file = new Regex(FILE_REGEX);
                Match m = file.Match(s);
                while (m.Success)
                {
                    result.Files.Add(result.Files.Count + 1, m.Groups[FILE].Value);
                    s = Match(ref file, ref result, ref m, s, FILE, "input-file-list");
                }
                return result;
            }
        }

        private class ArmARStringParser : StringParser
        {
            public ArmARStringParser(string name)
                : base(name)
            {
            }
            public override string Pattern
            {
                get
                {
                    return @"(?:\s|\A)(?<param>(?:-a|-b|-i|-m))\s*=?\s*(?<args>(?:(?:[a-zA-Z]:\\\\?)|\\\\?)?(?:[^\\/:""<>|\r\n\s]+\\\\?)*(?:[^\\/:""<>|\r\n\s]+)|""(?:(?:[a-zA-Z]:\\\\?)|\\\\?)?(?:[^\\/:""<>|\r\n]+\\\\?)*(?:[^\\/:""<>|\r\n]+)"")|(?:\s|\A)(?<param>-c|-C|--create|-d|--entries|--help|-n|--new_files_only|-p|-r|-ru|-s|--show_cmdline|--sizes|-t|-T|-u|-v|--vsn|-x|--zs|--zt)\b|(?:\s|\A)(?<param>(?:--diag_style))\s*=?\s*(?<args>\b(?:arm|ide|gnu)\b)|(?:\s|\A)(?<param>(?:--via))\s*=?\s*(?<args>(?:(?:[a-zA-Z]:\\\\?)|\\\\?)?(?:[^\\/:*?""<>|\r\n\s]+\\\\?)*(?:[^\\/:*?""<>|\r\n\s]+)|""(?:(?:[a-zA-Z]:\\\\?)|\\\\?)?(?:[^\\/:*?""<>|\r\n]+\\\\?)*(?:[^\\/:*?""<>|\r\n]+)"")";
                }
            }

            public override ParamCollection Parse(ref string s)
            {
                ParamCollection result = base.Parse(ref s);
                Regex file = new Regex(FILE_REGEX);
                Match m = file.Match(s);
                if (m.Success)
                {
                    s = Match(ref file, ref result, ref m, s, FILE, "archive");
                }
                while (m.Success)
                {
                    result.Files.Add(result.Files.Count + 1, m.Groups[FILE].Value);
                    s = Match(ref file, ref result, ref m, s, FILE, "file_list");
                }
                return result;
            }
        }


        const string ARMCC = "armcc.exe";
        const string ARMASM = "armasm.exe";
        const string ARMLINK = "armlink.exe";
        const string ARMAR = "armar.exe";

        static Dictionary<int, StringParser> Parsers = new Dictionary<int, StringParser>() { 
             {ARMCC.GetHashCode(), new ArmCCStringParser(ARMCC)}
             , {ARMASM.GetHashCode(), new ArmASMStringParser(ARMASM)}
             , {ARMLINK.GetHashCode(), new ArmLINKStringParser(ARMLINK)}
             , {ARMAR.GetHashCode(), new ArmARStringParser(ARMAR)}
        };


        private Match StartMatch(string s)
        {
            return Regex.Match(s, FILE_REGEX);
        }

        public string GetUtil(string s)
        {
            Match m = this.StartMatch(s);
            if (m.Success)
            {
                return m.Groups[FILE].Value;
            }
            else
            {
                return null;
            }
        }

        public ParamCollection Add(string s)
        {
            Match m = this.StartMatch(s);
            ParamCollection pc = null;
            if (m.Success)
            {
                s = s.Remove(m.Index, m.Length).Trim();
                string file_name = m.Groups[FILE_NAME].Value;
                if (file_name != null)
                {
                    StringParser parser;
                    if (Parsers.TryGetValue(file_name.GetHashCode(), out parser))
                    {
                        pc = Result[Result.Add(parser.Parse(ref s))];
                        foreach (string fname in pc.Files.Values)
                        {
                            //this.Files.Add(fname.Trim().GetHashCode(), pc);
                            this.Files.Add(Files.Count + 1, pc);
                        }
                    }
                }
            }
            return pc;
        }
    }
}

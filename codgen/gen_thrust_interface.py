
from collections import OrderedDict

# Generate header files and implementation wrappers for Thrust functions

class FuncInfo:
    def __init__(self, filename=None, func_name = None, template_params=None, return_type="void", function_args=None):
        self.filename = filename
        self.function_name = func_name
        self.template_parameters = template_params
        self.return_type = return_type
        self.function_arguments = function_args

# Example CPP wrapper implementation:
#        template<typename RandomAccessIterator1, typename RandomAccessIterator2>
#        void sort_by_key(RandomAccessIterator1 keys_first,
#                         RandomAccessIterator1 keys_last,
#                         RandomAccessIterator2 values_first)
#        {
#            thrust::sort_by_key(thrust::device, keys_first, keys_last, values_first);
#        }

    def print_wrapper_impl(self, host_or_device="thrust::device"):
        tdict = dict()
        tdict['targs'] = ", ".join(["typename " + t for t in self.template_parameters])
        tdict['ret_type'] = self.return_type
        tdict['func_name'] = self.function_name
        tdict['func_args_with_types'] = ", ".join(["{} {}".format(*fa) for fa in self.function_arguments])
        tdict['func_args'] = ", ".join(["{}".format(fa[1]) for fa in self.function_arguments])
        tdict['device'] = host_or_device
        tdict['maybe_return'] = "return" if self.return_type != "void" else ""

        s = """
        template<{targs}>
        {ret_type} {func_name}({func_args_with_types}) {{
           {maybe_return} thrust::{func_name}({device}, {func_args});
        }}
        """.format(**tdict)

        return s

# Example CPP wrapper include:
#    template <typename RandomAccessIterator1, typename RandomAccessIterator2>
#    void sort_by_key(RandomAccessIterator1 keys_first,
#                     RandomAccessIterator1 keys_last,
#                     RandomAccessIterator2 values_first);

    def print_wrapper_include(self):
        tdict = dict()
        tdict['targs'] = ", ".join(["typename " + t for t in self.template_parameters])
        tdict['ret_type'] = self.return_type
        tdict['func_name'] = self.function_name
        tdict['func_args_with_types'] = ", ".join(["{} {}".format(*fa) for fa in self.function_arguments])
        tdict['func_args'] = ", ".join(["{}".format(fa[1]) for fa in self.function_arguments])

        s = """
        template<{targs}>
        {ret_type} {func_name}({func_args_with_types});
        """.format(**tdict)

        return s

    # remove pointer indicators and qualifiers
    def base_type(self, tname):
        return tname.split('*')[0].strip()


# Example C name:
#   ompx_host_sort_by_key_int
    def mangle_c_name(self, td, place):
        type_set = OrderedDict()
        for fa in self.function_arguments:
            type_set[fa[0]] = None

        type_suffix = '_'.join([self.base_type(td[ts]) for ts in type_set.keys()])

        func_name = "ompx_{}_{}_{}".format(place, self.function_name, type_suffix)
        return func_name

# Example C wrapper include:
#   void ompx_host_sort_by_key_int(int* first, int* last);
    def print_wrapper_include_c(self, td, place):
        tdict = dict()
        # So far return type is void or bool, and doesn't need mapping
        tdict['ret_type'] = self.return_type 
        tdict['func_name'] = self.mangle_c_name(td, place)
        tdict['func_args_with_types'] = ", ".join(["{} {}".format(td[fa[0]],fa[1]) for fa in self.function_arguments])
        tdict['func_args'] = ", ".join(["{}".format(fa[1]) for fa in self.function_arguments])

        s = """
        {ret_type} {func_name}({func_args_with_types});
        """.format(**tdict)

        return s

# Example C wrapper implementation:
#   void ompx_host_sort_by_key(int* first, int* last) {
#     thrust::sort(thrust::device, first, last);
#   }
    def print_wrapper_impl_c(self, td, place, host_or_device="thrust::device"):
        tdict = dict()
        tdict['targs'] = ", ".join(["typename " + t for t in self.template_parameters])
        tdict['ret_type'] = self.return_type
        tdict['mangled_func_name'] = self.mangle_c_name(td, place)
        tdict['func_name'] = self.function_name
        tdict['func_args_with_types'] = ", ".join(["{} {}".format(td[fa[0]], fa[1]) for fa in self.function_arguments])
        tdict['func_args'] = ", ".join(["{}".format(fa[1]) for fa in self.function_arguments])
        tdict['device'] = host_or_device
        tdict['maybe_return'] = "return" if self.return_type != "void" else ""

        s = """
        {ret_type} {mangled_func_name}({func_args_with_types}) {{
           {maybe_return} thrust::{func_name}({device}, {func_args});
        }}
        """.format(**tdict)

        return s

# Example explicit instantiation:
#    template void ompx::device::sort_by_key(int*, int*, double*);
    def print_wrapper_inst(self, type_dict, namespace="device"):
        tdict = dict()
        tdict['ret_type'] = self.return_type
        tdict['func_name'] = self.function_name
        tdict['ns'] = namespace
        arg_types = [type_dict[arg[0]] for arg in self.function_arguments]
        tdict['args'] = ", ".join(arg_types)

        s = "template {ret_type} ompx::{ns}::{func_name}({args});".format(**tdict)
        return s



def output_incl(func_info_list):

    inc = ""
    for fi in func_info_list:
        inc += fi.print_wrapper_include()
    s = """
#ifndef OMPX_SORT_H
#define OMPX_SORT_H

namespace ompx
{{
    namespace host
    {{
      {declarations}
    }}

    namespace device
    {{
      {declarations}
    }}
}}
#endif
""".format(declarations=inc)

    return s

def output_incl_c(func_info_list, type_dict_list):

    inst_host_set = OrderedDict()
    for fi in func_info_list:
        for td in type_dict_list:
            inst_host_set[fi.print_wrapper_include_c(td,"host")] = None

    inc_host = ""
    for s in inst_host_set.keys():
        inc_host += s

    inst_device_set = OrderedDict()
    for fi in func_info_list:
        for td in type_dict_list:
            inst_device_set[fi.print_wrapper_include_c(td,"device")] = None

    inc_device = ""
    for s in inst_device_set.keys():
        inc_device += s

    s = """
#ifndef OMPX_CSORT_H
#define OMPX_CSORT_H

#ifdef __cplusplus
extern "C" {{
#endif
{declarations_host}

{declarations_device}
#ifdef __cplusplus
}}
#endif

#endif
""".format(declarations_host=inc_host, declarations_device=inc_device)

    return s

def output_impl(func_info_list):
    impl_host = ""
    for fi in func_info_list:
        impl_host += fi.print_wrapper_impl(host_or_device="thrust::host")

    impl_device = ""
    for fi in func_info_list:
        impl_device += fi.print_wrapper_impl(host_or_device="thrust::device")

    s = """
#include "thrust/sort.h"

namespace ompx
{{
    namespace host
    {{
      {impl_host}
    }}

    namespace device
    {{
      {impl_device}
    }}
}}
""".format(impl_host=impl_host, impl_device=impl_device)

    return s

def output_impl_c(func_info_list):
    inst_host_set = OrderedDict()
    for fi in func_info_list:
        for td in type_dict_list:
            inst_host_set[fi.print_wrapper_impl_c(td,"host",host_or_device="thrust::host")] = None

    impl_host = ""
    for s in inst_host_set.keys():
        impl_host += s

    inst_device_set = OrderedDict()
    for fi in func_info_list:
        for td in type_dict_list:
            inst_device_set[fi.print_wrapper_impl_c(td,"device",host_or_device="thrust::device")] = None

    impl_device = ""
    for s in inst_device_set.keys():
        impl_device += s

    s = """
#include "thrust/sort.h"

extern "C" {{
{impl_host}

{impl_device}
}}
""".format(impl_host=impl_host, impl_device=impl_device)

    return s


def output_explicit_inst(func_info_list, type_dict_list):

    # hack to prevent duplicates - put all the instantations in set first
    #inst_host_set = set()
    inst_host_set = OrderedDict()
    for fi in func_info_list:
        for td in type_dict_list:
            inst_host_set[fi.print_wrapper_inst(td,namespace="host")] = None

    #inst_device_set = set()
    inst_device_set = OrderedDict()
    for fi in func_info_list:
        for td in type_dict_list:
            inst_device_set[fi.print_wrapper_inst(td,namespace="device")] = None

    inst_host = ""
    for s in inst_host_set.keys():
        inst_host += s + "\n"

    inst_device = ""
    for s in inst_device_set.keys():
        inst_device += s + "\n"

    return inst_host + inst_device


def generate_output_files(fi_list, type_dict_list):
    # C++ include header
    s_inc = output_incl(fi_list)
    fname_inc = "sort.h"
    with open(fname_inc,"w") as f:
        f.write(s_inc)

    # Should the C interface be in a separate include file from the C++ interface?
    # If separate, how should it be done? Name? Directory?
    # C include header
    s_inc_c = output_incl_c(fi_list, type_dict_list)
    fname_inc_c = "csort.h"
    with open(fname_inc_c,"w") as f:
        f.write(s_inc_c)

    # C implementation
    s_impl_c = output_impl_c(fi_list)
    fname_impl_c = "csort_impl.cu"
    with open(fname_impl_c,"w") as f:
        f.write(s_impl_c)

    # C++ implementation
    s_impl = output_impl(fi_list)
    s_expl = output_explicit_inst(fi_list, type_dict_list)
    fname_impl = "sort_impl.cu"
    with open(fname_impl,"w") as f:
        f.write(s_impl)
        f.write("// Explicit instantiations\n")
        f.write(s_expl)
 

if __name__ == '__main__':
    # List of argument types
    RA = "RandomAccessIterator"
    RA1 = "RandomAccessIterator1"
    RA2 = "RandomAccessIterator2"

    # List of thrust functions and argument types
    fi_list = [
        FuncInfo("sort", "sort", [RA], "void", [(RA, "first"), (RA, "last")]),
        FuncInfo("sort", "stable_sort", [RA], "void", [(RA, "first"), (RA, "last")]),
        FuncInfo("sort", "sort_by_key", [RA1, RA2], "void", [(RA1, "keys_first"), (RA1, "keys_last"), (RA2, "values_first")]),
        FuncInfo("sort", "stable_sort_by_key", [RA1, RA2], "void", [(RA1, "keys_first"), (RA1, "keys_last"), (RA2, "values_first")]),
        ]

    # Should these functions be included?
    #     FuncInfo("sort", "is_sorted", [RA], "bool", [(RA, "first"), (RA, "last")]),
    #     FuncInfo("sort", "is_sorted_until", [RA], "bool", [(RA, "first"), (RA, "last")]),

    # List of types for explicit instantiations
    #type_dict = {RA: "int *", RA1: "int *", RA2: "double *"}
    type_dict_list = [
            {RA: "int *", RA1: "int *", RA2: "double *"},
            {RA: "int *", RA1: "int *", RA2: "int *"}
            ]
    #type_dict = {RA1: "int *"}
    #print(fi.print_wrapper_inst(type_dict, namespace="host"))
    #print(fi2.print_wrapper_inst(type_dict))

    generate_output_files(fi_list, type_dict_list)


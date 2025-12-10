/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       notes
 * 2025-10-29     foxglove     Command export macro module
 */

use darling::FromMeta;
use proc_macro::TokenStream;
use proc_macro2::{Literal, Span};
use syn::{parse_macro_input, spanned::Spanned, ReturnType, Visibility, Meta};
use syn::parse::Parser;
use syn::NestedMeta as DarlingNestedMeta;

#[derive(Debug, FromMeta)]
struct CmdArgs {
    #[darling(default)]
    name: Option<String>,
    #[darling(default)]
    desc: Option<String>,
}

/** RT-Thread Shell command export macro
 
 Used to export a function as an RT-Thread Shell command
 
 Usage:
 ```rust
 #[msh_cmd_export(name = "my_cmd", desc = "My command description")]
 fn my_command(args: vec::IntoIter<rt_rust::param::ParamItem>) {
     // Command logic
 }
 ```
*/
pub fn msh_cmd_export(args: TokenStream, input: TokenStream) -> TokenStream {
    let f = parse_macro_input!(input as syn::ItemFn);
    let parser = syn::punctuated::Punctuated::<Meta, syn::token::Comma>::parse_terminated;
    let raw_meta = match parser.parse(args) {
        Ok(v) => v,
        Err(e) => return e.to_compile_error().into(),
    };
    let raw_arg: Vec<DarlingNestedMeta> = raw_meta
        .into_iter()
        .map(DarlingNestedMeta::Meta)
        .collect();
    let parg = CmdArgs::from_list(&raw_arg).map_err(|e| e.write_errors());
    let arg = match parg {
        Ok(x) => x,
        Err(e) => {
            return e.into();
        }
    };

    if arg.name.is_none() {
        return syn::parse::Error::new(
            Span::call_site(),
            "`#[msh_cmd_export]` macro must have attribute `name`",
        )
        .to_compile_error()
        .into();
    }

    let main_func_name = format_ident!("__{}_main_func", arg.name.as_ref().unwrap());
    let cmd_seg_name = format_ident!("__{}_cmd_seg", arg.name.as_ref().unwrap());
    let cmd_struct_name = format_ident!("__{}_cmd_seg_struct", arg.name.as_ref().unwrap());
    let cmd_namestr_name = format_ident!("__{}_cmd_namestr", arg.name.as_ref().unwrap());
    let cmd_descstr_name = format_ident!("__{}_cmd_descstr", arg.name.as_ref().unwrap());
    let mod_name = format_ident!("__cmd_func_{}_", arg.name.as_ref().unwrap());
    let call_func_name = f.sig.ident.clone();

    /* Check function signature */
    let valid_signature = f.sig.constness.is_none()
        && f.sig.unsafety.is_none()
        && f.sig.asyncness.is_none()
        && f.vis == Visibility::Inherited
        && f.sig.abi.is_none()
        && f.sig.inputs.len() == 1
        && f.sig.generics.params.is_empty()
        && f.sig.generics.where_clause.is_none()
        && f.sig.variadic.is_none()
        && match f.sig.output {
            ReturnType::Default => true,
            _ => false,
        };

    if !valid_signature {
        return syn::parse::Error::new(
            f.span(),
            "`#[msh_cmd_export]` function must have signature `fn(args: vec::IntoIter<rt_rust::param::ParamItem>)`",
        )
        .to_compile_error()
        .into();
    }

    let attrs = f.attrs.clone();

    let origin = quote!(
        #(#attrs)*
        #f
    );

    let desc = arg.desc.map_or(String::from("No desc\0"), |mut x| {
        x.push_str("\0");
        x
    });
    let r_desc = Literal::byte_string(desc.as_bytes());

    let mut cmd_name = arg.name.as_ref().unwrap().clone();
    cmd_name.push_str("\0");
    let r_cmd_name = Literal::byte_string(cmd_name.as_bytes());

    let desc_len = desc.len();
    let cmd_name_len = cmd_name.len();

    let core = quote!(
        #[no_mangle]
        pub unsafe extern "C" fn #main_func_name(argc: u32, argv: *const *const u8) {
            use core::iter::Iterator;
            use rt_rust::param::ParamItem;
            let vec = {
                (0..argc as isize)
                    .map(|i| {
                        let mut len = 0usize;
                        loop {
                            if *(*argv.offset(i)).offset(len as isize) != b'\0' {
                                len += 1;
                            } else {
                                break
                            }
                        }
                        ParamItem::new(core::slice::from_raw_parts::<'static, _>(*argv.offset(i), len))
                    })
                    .collect::<Vec<_>>()
            };
            #call_func_name(vec.into_iter())
        }
    );

    let cmd_seg = quote!(
        #[link_section = ".rodata.name"]
        #[no_mangle]
        static #cmd_namestr_name: [u8; #cmd_name_len] = *#r_cmd_name;
        #[link_section = ".rodata.name"]
        #[no_mangle]
        static #cmd_descstr_name: [u8; #desc_len] = *#r_desc;

        #[repr(C)]
        struct #cmd_struct_name {
            name: *const u8,
            desc: *const u8,
            opt: *const core::ffi::c_void,
            func: extern "C" fn(argc: u32, argv: *const *const u8) -> i32,
        }
        unsafe impl Sync for #cmd_struct_name{}

        extern "C" fn __wrap_main(argc: u32, argv: *const *const u8) -> i32 {
            unsafe { #main_func_name(argc, argv); }
            0
        }

        #[link_section = "FSymTab"]
        #[no_mangle]
        static #cmd_seg_name: #cmd_struct_name = #cmd_struct_name {
            name: #cmd_namestr_name.as_ptr(),
            desc: #cmd_descstr_name.as_ptr(),
            opt: core::ptr::null(),
            func: __wrap_main,
        };
    );

    quote!(
        #origin
        mod #mod_name {
            use super::#call_func_name;
            use core::marker::Sync;
            extern crate alloc;
            use alloc::vec::Vec;
            use core::iter::IntoIterator;

            #core
            #cmd_seg
        }
    )
    .into()
}

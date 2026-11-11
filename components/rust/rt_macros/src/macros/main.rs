/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       notes
 * 2025-10-29     foxglove     Main thread entry macro module
 */

use darling::FromMeta;
use proc_macro::TokenStream;
use proc_macro2::Span;
use syn::{parse_macro_input, spanned::Spanned, ReturnType, Visibility, Meta};
use syn::parse::Parser;
use syn::NestedMeta as DarlingNestedMeta;

#[derive(Debug, FromMeta)]
struct MainArgs {
    #[darling(default)]
    name: Option<String>,
}

/** RT-Thread main thread entry macro
 
 Used to mark the main entry function of a Rust program, exporting it as 
 a main thread entry recognizable by RT-Thread
 
 Usage:
 ```rust
 #[rt_thread_main]
 fn main() {
     // Main thread logic
 }
 ```
 
 Or specify a name:
 ```rust
 #[rt_thread_main(name = "my_main")]
 fn main() {
     // Main thread logic
 }
 ```
*/
pub fn rt_thread_main(args: TokenStream, input: TokenStream) -> TokenStream {
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
    let parg = MainArgs::from_list(&raw_arg).map_err(|e| e.write_errors());
    let arg = match parg {
        Ok(x) => x,
        Err(e) => {
            return e.into();
        }
    };

    if arg.name.is_none() {
        return syn::parse::Error::new(
            Span::call_site(),
            "`#[rt_thread_main]` macro must have attribute `name`",
        )
        .to_compile_error()
        .into();
    }

    let main_func_name = format_ident!("__{}_main_func", arg.name.as_ref().unwrap());
    let mod_name = format_ident!("__init_func_{}_", arg.name.as_ref().unwrap());
    let call_func_name = f.sig.ident.clone();

    /* Check function signature */  
    let valid_signature = f.sig.constness.is_none()
        && f.sig.unsafety.is_none()
        && f.sig.asyncness.is_none()
        && f.vis == Visibility::Inherited
        && f.sig.abi.is_none()
        && f.sig.inputs.is_empty()
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
            "`#[rt_thread_main]` function must have signature `fn()`",
        )
        .to_compile_error()
        .into();
    }

    let attrs = f.attrs.clone();

    let origin = quote!(
        #(#attrs)*
        #f
    );

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

    quote!(
        #origin
        mod #mod_name {
            use super::#call_func_name;
            extern crate alloc;
            use alloc::vec::Vec;
            use core::iter::IntoIterator;

            #core
        }
    )
    .into()
}

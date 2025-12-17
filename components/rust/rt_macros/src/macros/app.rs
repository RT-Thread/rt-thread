/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       notes
 * 2025-10-29     foxglove     Application export macro module
 */

use darling::FromMeta;
use proc_macro::TokenStream;
use proc_macro2::Span;
use syn::{parse_macro_input, spanned::Spanned, ReturnType, Visibility, Meta};
use syn::parse::Parser;
use syn::NestedMeta as DarlingNestedMeta;

#[derive(Debug, FromMeta)]
struct AppArgs {
    #[darling(default)]
    name: Option<String>,
}

/** RT-Thread application export macro
 
 Used to export a function as an RT-Thread application initialization entry
 
 Usage:
 ```rust
 #[rt_app_export]
 fn my_app_init() {
     // Application initialization logic
 }
 ```
 
 Or specify a name:
 ```rust
 #[rt_app_export(name = "my_app")]
 fn my_app_init() {
     // Application initialization logic
 }
 ```
*/
pub fn rt_app_export(args: TokenStream, input: TokenStream) -> TokenStream {
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
    let parg = AppArgs::from_list(&raw_arg).map_err(|e| e.write_errors());
    let arg = match parg {
        Ok(x) => x,
        Err(e) => {
            return e.into();
        }
    };

    if arg.name.is_none() {
        return syn::parse::Error::new(
            Span::call_site(),
            "`#[rt_app_export]` macro must have attribute `name`",
        )
        .to_compile_error()
        .into();
    }

    let app_seg_name = format_ident!("__{}_app_seg", arg.name.as_ref().unwrap());
    let app_func_name = format_ident!("__{}_app_func", arg.name.as_ref().unwrap());
    let app_struct_name = format_ident!("__{}_app_seg_struct", arg.name.as_ref().unwrap());
    let mod_name = format_ident!("__app_func_{}_", arg.name.as_ref().unwrap());
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
            "`#[rt_app_export]` function must have signature `fn()`",
        )
        .to_compile_error()
        .into();
    }

    let attrs = f.attrs.clone();

    let origin = quote!(
        #(#attrs)*
        #f
    );

    let app_seg = quote!(
        struct #app_struct_name (*const ());
        unsafe impl Sync for #app_struct_name{}

        #[no_mangle]
        pub unsafe extern "C" fn #app_func_name() -> i32 {
            #call_func_name();
            0
        }

        #[link_section = ".rti_fn.6"]
        #[no_mangle]
        static #app_seg_name: #app_struct_name
            = #app_struct_name (#app_func_name as *const ());
    );

    quote!(
        #origin
        mod #mod_name {
            use super::#call_func_name;
            use core::marker::Sync;

            #app_seg
        }
    )
    .into()
}

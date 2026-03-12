/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       notes
 * 2025-10-29     foxglove     Component export macro module
 */

use darling::FromMeta;
use proc_macro::TokenStream;
use proc_macro2::Span;
use syn::{parse_macro_input, spanned::Spanned, ReturnType, Visibility, Meta};
use syn::parse::Parser;
use syn::NestedMeta as DarlingNestedMeta;

#[derive(Debug, FromMeta)]
struct ComponentArgs {
    #[darling(default)]
    name: Option<String>,
}

/** RT-Thread component export macro
 
 Used to export a function as an RT-Thread component initialization entry
 
 Usage:
 ```rust
 #[rt_component_export]
 fn my_component_init() {
     // Component initialization logic
 }
 ```
 
 Or specify a name:
 ```rust
 #[rt_component_export(name = "my_component")]
 fn my_component_init() {
     // Component initialization logic
 }
 ```
*/
pub fn rt_component_export(args: TokenStream, input: TokenStream) -> TokenStream {
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
    let parg = ComponentArgs::from_list(&raw_arg).map_err(|e| e.write_errors());
    let arg = match parg {
        Ok(x) => x,
        Err(e) => {
            return e.into();
        }
    };

    if arg.name.is_none() {
        return syn::parse::Error::new(
            Span::call_site(),
            "`#[rt_component_export]` macro must have attribute `name`",
        )
        .to_compile_error()
        .into();
    }

    let component_seg_name = format_ident!("__{}_component_seg", arg.name.as_ref().unwrap());
    let component_func_name = format_ident!("__{}_component_func", arg.name.as_ref().unwrap());
    let component_struct_name = format_ident!("__{}_component_seg_struct", arg.name.as_ref().unwrap());
    let mod_name = format_ident!("__component_func_{}_", arg.name.as_ref().unwrap());
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
            "`#[rt_component_export]` function must have signature `fn()`",
        )
        .to_compile_error()
        .into();
    }

    let attrs = f.attrs.clone();

    let origin = quote!(
        #(#attrs)*
        #f
    );

    let component_seg = quote!(
        struct #component_struct_name (*const ());
        unsafe impl Sync for #component_struct_name{}

        #[no_mangle]
        pub unsafe extern "C" fn #component_func_name() -> i32 {
            #call_func_name();
            0
        }

        #[link_section = ".rti_fn.4"]
        #[no_mangle]
        static #component_seg_name: #component_struct_name
            = #component_struct_name (#component_func_name as *const ());
    );

    quote!(
        #origin
        mod #mod_name {
            use super::#call_func_name;
            use core::marker::Sync;

            #component_seg
        }
    )
    .into()
}

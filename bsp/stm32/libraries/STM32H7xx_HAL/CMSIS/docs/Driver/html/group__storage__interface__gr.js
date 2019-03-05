var group__storage__interface__gr =
[
    [ "Use of Storage APIs", "group__StorageDriverFunctions.html", null ],
    [ "Sample Use of Storage Driver", "group__SampleUseOfStorageDriver.html", null ],
    [ "ARM_STORAGE_BLOCK_ATTRIBUTES", "group__storage__interface__gr.html#structARM__STORAGE__BLOCK__ATTRIBUTES", [
      [ "erasable", "group__storage__interface__gr.html#ab350afb2119388ebd3f096bd24f019ef", null ],
      [ "programmable", "group__storage__interface__gr.html#a7f4aebaeeb818b0e2a0592f96559fa1b", null ],
      [ "executable", "group__storage__interface__gr.html#a910da8e2e909faab1d32cca7f8b05656", null ],
      [ "protectable", "group__storage__interface__gr.html#a7c8899f46a471e1b7698a75a759e67c1", null ],
      [ "reserved", "group__storage__interface__gr.html#aa43c4c21b173ada1b6b7568956f0d650", null ],
      [ "erase_unit", "group__storage__interface__gr.html#aac21d3f798c9fcad415b99cf4157935a", null ],
      [ "protection_unit", "group__storage__interface__gr.html#ae319384dfb356cbb0b08ccbf8c04a590", null ]
    ] ],
    [ "ARM_STORAGE_BLOCK", "group__storage__interface__gr.html#structARM__STORAGE__BLOCK", [
      [ "addr", "group__storage__interface__gr.html#a0e89cf6b9f6cd3125470b1bed2b823df", null ],
      [ "size", "group__storage__interface__gr.html#af931a8871310b4dad23f0f0b0f623560", null ],
      [ "attributes", "group__storage__interface__gr.html#ade62c905888479b4f6d078d45cec5830", null ]
    ] ],
    [ "ARM_STORAGE_INFO", "group__storage__interface__gr.html#structARM__STORAGE__INFO", [
      [ "total_storage", "group__storage__interface__gr.html#a4b14ce1ca2ceea5ce49e81348c5b38f6", null ],
      [ "program_unit", "group__storage__interface__gr.html#a483c41066757e2865bf3a27a2a627a54", null ],
      [ "optimal_program_unit", "group__storage__interface__gr.html#a407e16dc7e4da08cea7785efeebd9b6d", null ],
      [ "program_cycles", "group__storage__interface__gr.html#ac501623ba5adb4904cdd6c286e7388eb", null ],
      [ "erased_value", "group__storage__interface__gr.html#a902510dbedab116ab6a260a83fbd0f27", null ],
      [ "memory_mapped", "group__storage__interface__gr.html#a616b41da466430ed481d791e63784f0c", null ],
      [ "programmability", "group__storage__interface__gr.html#aac0da06bf0775bd9b877aafbc4bcad77", null ],
      [ "retention_level", "group__storage__interface__gr.html#a16d1a2aead689ffa28fd89cb6779e5a7", null ],
      [ "reserved", "group__storage__interface__gr.html#aa43c4c21b173ada1b6b7568956f0d650", null ],
      [ "security", "group__storage__interface__gr.html#aee43dd20848f45fe05efc10a8198817a", null ]
    ] ],
    [ "ARM_DRIVER_STORAGE", "group__storage__interface__gr.html#structARM__DRIVER__STORAGE", [
      [ "GetVersion", "group__storage__interface__gr.html#a8834b281da48583845c044a81566c1b3", null ],
      [ "GetCapabilities", "group__storage__interface__gr.html#abbfb3aa4b6adb4407de79221bf12cc55", null ],
      [ "Initialize", "group__storage__interface__gr.html#a4a126668a113ce450b0d831c74199b23", null ],
      [ "Uninitialize", "group__storage__interface__gr.html#adcf20681a1402869ecb5c6447fada17b", null ],
      [ "PowerControl", "group__storage__interface__gr.html#aba8f1c8019af95ffe19c32403e3240ef", null ],
      [ "ReadData", "group__storage__interface__gr.html#a79b015933daca07a88f98a8f20e1144d", null ],
      [ "ProgramData", "group__storage__interface__gr.html#aedda6cc77ea7c4ef2356c683f9013d8b", null ],
      [ "Erase", "group__storage__interface__gr.html#abb5018d1afb3ea4632e6e6006314f37f", null ],
      [ "EraseAll", "group__storage__interface__gr.html#ad4dc5af362c0f2043138618aea9c6a73", null ],
      [ "GetStatus", "group__storage__interface__gr.html#a820e9b9de75ebe93e64b067468b369af", null ],
      [ "GetInfo", "group__storage__interface__gr.html#aec80a5d1ccf1cd996f6e863ac8868d65", null ],
      [ "ResolveAddress", "group__storage__interface__gr.html#a6e1b3f9abb40bb5c70c6141587ee6e6a", null ],
      [ "GetNextBlock", "group__storage__interface__gr.html#adda93f4d74519247517f036c4551dd13", null ],
      [ "GetBlock", "group__storage__interface__gr.html#af43edebfb5463d22ffeda6de20e1d1bd", null ]
    ] ],
    [ "ARM_STORAGE_CAPABILITIES", "group__storage__interface__gr.html#structARM__STORAGE__CAPABILITIES", [
      [ "asynchronous_ops", "group__storage__interface__gr.html#a15ade4ca762bc6ce72d435a16febb4cc", null ],
      [ "erase_all", "group__storage__interface__gr.html#a63882f6a571f20aad1b5b3542cdaafa1", null ],
      [ "reserved", "group__storage__interface__gr.html#aa43c4c21b173ada1b6b7568956f0d650", null ]
    ] ],
    [ "ARM_STORAGE_STATUS", "group__storage__interface__gr.html#structARM__STORAGE__STATUS", [
      [ "busy", "group__storage__interface__gr.html#a50c88f3c1d787773e2ac1b59533f034a", null ],
      [ "error", "group__storage__interface__gr.html#aa8d183302fdfa4a6892f1d80300cdb32", null ],
      [ "reserved", "group__storage__interface__gr.html#aa43c4c21b173ada1b6b7568956f0d650", null ]
    ] ],
    [ "ARM_Storage_Callback_t", "group__storage__interface__gr.html#ga4b290224fea782e6d2ad06f541b28a98", null ],
    [ "ARM_STORAGE_OPERATION", "group__storage__interface__gr.html#ga3a9277f89946d61c41b22da72e3eef7c", [
      [ "ARM_STORAGE_OPERATION_GET_VERSION", "Driver__Storage_8h.html#ga3a9277f89946d61c41b22da72e3eef7cac82e2ca0f9b7ec94e24ae56c45f12f8c", null ],
      [ "ARM_STORAGE_OPERATION_GET_CAPABILITIES", "Driver__Storage_8h.html#ga3a9277f89946d61c41b22da72e3eef7ca314621ae4384fef7094d8724d59b65c4", null ],
      [ "ARM_STORAGE_OPERATION_INITIALIZE", "Driver__Storage_8h.html#ga3a9277f89946d61c41b22da72e3eef7caca3985b874bf393dc2e448b339668971", null ],
      [ "ARM_STORAGE_OPERATION_UNINITIALIZE", "Driver__Storage_8h.html#ga3a9277f89946d61c41b22da72e3eef7cab9488e567ad58b16c5df2637df3902e9", null ],
      [ "ARM_STORAGE_OPERATION_POWER_CONTROL", "Driver__Storage_8h.html#ga3a9277f89946d61c41b22da72e3eef7ca213a74ac5a692a80f17fd6d8e6565e05", null ],
      [ "ARM_STORAGE_OPERATION_READ_DATA", "Driver__Storage_8h.html#ga3a9277f89946d61c41b22da72e3eef7ca177812f3cb27c413473d94ebe9480454", null ],
      [ "ARM_STORAGE_OPERATION_PROGRAM_DATA", "Driver__Storage_8h.html#ga3a9277f89946d61c41b22da72e3eef7ca586b4774a7a092d1932d3415cc42abb0", null ],
      [ "ARM_STORAGE_OPERATION_ERASE", "Driver__Storage_8h.html#ga3a9277f89946d61c41b22da72e3eef7cab52a1d10b8087452fd97af8cdb9a6f75", null ],
      [ "ARM_STORAGE_OPERATION_ERASE_ALL", "Driver__Storage_8h.html#ga3a9277f89946d61c41b22da72e3eef7ca60a0511bd5e32db2a22d3ab2023a601e", null ],
      [ "ARM_STORAGE_OPERATION_GET_STATUS", "Driver__Storage_8h.html#ga3a9277f89946d61c41b22da72e3eef7ca7c595cd3c439753efe0a0b17efd7bb7f", null ],
      [ "ARM_STORAGE_OPERATION_GET_INFO", "Driver__Storage_8h.html#ga3a9277f89946d61c41b22da72e3eef7ca0fe0ef7c0a9e69d053a0419282248f40", null ],
      [ "ARM_STORAGE_OPERATION_RESOLVE_ADDRESS", "Driver__Storage_8h.html#ga3a9277f89946d61c41b22da72e3eef7ca3292512d0222e4119d0cdf77de1508df", null ],
      [ "ARM_STORAGE_OPERATION_GET_NEXT_BLOCK", "Driver__Storage_8h.html#ga3a9277f89946d61c41b22da72e3eef7ca9bfab6ee9caa3ace32338d4ef2d856f5", null ],
      [ "ARM_STORAGE_OPERATION_GET_BLOCK", "Driver__Storage_8h.html#ga3a9277f89946d61c41b22da72e3eef7cac75096931c3d29af1029f25fc44e7523", null ]
    ] ],
    [ "ARM_Storage_GetVersion", "group__storage__interface__gr.html#gaf28193431b1a2ee64b22bfb36aed27e3", null ],
    [ "ARM_Storage_GetCapabilities", "group__storage__interface__gr.html#ga8378b3901dfe76d8f31728a50e10dae2", null ],
    [ "ARM_Storage_Initialize", "group__storage__interface__gr.html#gacc5dc090a35ac16caff8957030eaa174", null ],
    [ "ARM_Storage_Uninitialize", "group__storage__interface__gr.html#ga1d14b15ddcda2836c6e3c1d0b5e60dca", null ],
    [ "ARM_Storage_PowerControl", "group__storage__interface__gr.html#ga979a2484bf05b2986de95a5d98307d54", null ],
    [ "ARM_Storage_ReadData", "group__storage__interface__gr.html#gabaa24553c165add98020434c980b3ab4", null ],
    [ "ARM_Storage_ProgramData", "group__storage__interface__gr.html#gabd20d561854c06918b0515b6c1bba230", null ],
    [ "ARM_Storage_Erase", "group__storage__interface__gr.html#gaceef4851d9181cce65c8b2d05f4429bc", null ],
    [ "ARM_Storage_EraseAll", "group__storage__interface__gr.html#ga04e77387a3c628d6fc661e82f7daddaa", null ],
    [ "ARM_Storage_GetStatus", "group__storage__interface__gr.html#ga29e7bfe78f41abb16973bdb4e0188a20", null ],
    [ "ARM_Storage_GetInfo", "group__storage__interface__gr.html#gad557e8e6e33cd4528d398ecf4dddc747", null ],
    [ "ARM_Storage_ResolveAddress", "group__storage__interface__gr.html#ga5a1934750a51c74b8b0fea52588a3b9a", null ],
    [ "ARM_Storage_GetNextBlock", "group__storage__interface__gr.html#gad318f8cb38626cbeea1fcf36a0977c44", null ],
    [ "ARM_Storage_GetBlock", "group__storage__interface__gr.html#ga5fe9d27ce8afe65124dec62566114073", null ]
];
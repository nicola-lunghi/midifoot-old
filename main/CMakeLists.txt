set(srcs "app_main.c"
         "app_intro.c"
         "app_storage.c"
         "app_button.c"
         )
set(includes ".")
set(priv_requires "button" "nvs_flash")

idf_component_register(SRCS ${srcs}
                       INCLUDE_DIRS ${includes}
                       PRIV_REQUIRES ${priv_requires})


set(srcs "app_main.c")
set(includes ".")
set(priv_requires "esp_wrover_kit")

idf_component_register(SRCS ${srcs}
                       INCLUDE_DIRS ${includes}
                       PRIV_REQUIRES ${priv_requires})


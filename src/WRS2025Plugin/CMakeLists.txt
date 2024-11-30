set(sources
  WRS2025Plugin.cpp
)

set(headers

)

set(target CnoidWRS2025Plugin)
choreonoid_make_gettext_mo_files(${target} mofiles)
choreonoid_add_plugin(${target} ${sources} ${mofiles} HEADERS ${headers})
target_link_libraries(${target} PUBLIC CnoidBodyPlugin CnoidWRSUtilPlugin)
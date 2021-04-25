set_languages('cxx14')

target('demo')
set_kind('binary')

add_links('lua')
add_linkdirs("/usr/local/Cellar/lua/5.4.3/lib")

--add lua headers
add_includedirs(os.getenv('LUA_HEADERS'))

add_files('$(projectdir)/src/main.cpp')

before_build(function(target)
    -- do something here before building it
end)

after_build(function(target)
    print("hello: %s", target:name())
    os.exec("echo %s", target:targetfile())
end)
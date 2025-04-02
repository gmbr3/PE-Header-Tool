project('pe_header_tool', 'cpp',
  version : '0.1',
  meson_version : '>=1.4.0',
  default_options : ['warning_level=3', 'cpp_std=gnu++17'])

qt6 = import('qt6')
qt6_dep = dependency('qt6', modules: ['Widgets'])

ui_cpp_files = []
uic_files = []
moc_files = []
uic_out = []
moc_out = []

subdir('ui')

foreach name : uic_files
  uic_out += qt6.compile_ui(sources : name)
endforeach

foreach name : moc_files
  moc_out += qt6.compile_moc(headers : name,
                            dependencies: qt6_dep)
endforeach


cc_files = ['file_header.cc', 'optional_header.cc', 'main.cc']

executable('pe_header_tool',
           cc_files,
           moc_files,
           ui_cpp_files,
           uic_out,
           moc_out,
           dependencies: qt6_dep,
           install : true)

import os

srcdir = '.'
blddir = './build'
VERSION = '0.0.2'

def set_options(opt):
  opt.tool_options('compiler_cxx')

def configure(conf):
  conf.check_tool('compiler_cxx')


def build(bld):
  monkey = bld.new_task_gen('cxx')
  monkey.cxxflags = ['-g','-Wall', '-pedantic','-lxerces-c']
  monkey.target = 'symxml'
  monkey.source = ['main.cc', 'symphony-xml.cc']


    
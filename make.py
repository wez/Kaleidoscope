#!/usr/bin/env python
import os
import sys
# Pull in our build library
sys.path.insert(0, os.path.join(os.path.dirname(__file__), 'build'))

import argparse
import Arduino

def discover_projects(dir):
    ''' Look for buildable projects under dir '''
    projects = {}

    def sketch_file(files):
        for f in files:
            _, ext = os.path.splitext(f)
            if ext == '.ino':
                return f
        return None

    for projdir, dirs, files in os.walk(dir):
        sketch = sketch_file(files)
        if sketch:
            projects[projdir] = {
                'dir': projdir,
                'sketch': sketch,
                'fqbn': 'keyboardio:avr:model01'}

    return projects

def compute_targets():
    ''' Locate all buildable projects '''
    projects = {}
    for libdir, dirs, files in os.walk('libraries'):
        if 'library.properties' in files and 'examples' in dirs:
            projects.update(discover_projects(os.path.join(libdir, 'examples')))

    projects.update(discover_projects('projects'))
    return projects

def build_project(project, verbose):
    ''' Build a project '''

    print('Building %s' % project_name)

    build_dir = os.path.join('output', project['dir'])
    if not os.path.isdir(build_dir):
        os.makedirs(build_dir)

    arduino.compile_sketch(os.path.join(project['dir'], project['sketch']),
                           project['fqbn'],
                           build_path=build_dir,
                           verbose=verbose,
                           prefs={'compiler.cpp.extra_flags': ' '.join([
                               '-std=c++11',
                               '-Woverloaded-virtual',
                               '-Wno-unused-parameter',
                               '-Wno-unused-variable',
                               '-Wno-ignored-qualifiers'])})

def flash_project(project, verbose, port):
    ''' Flash a project '''

    build_project(project, verbose)

    print('TODO: actually flash it (I have this code in another repo)')


parser = argparse.ArgumentParser(description='''
    build keyboardio firmware
    ''')
parser.add_argument('--build', metavar='project', help='which project to build', nargs='+')
parser.add_argument('--build-all', help='build all projects', action='store_true')
parser.add_argument('--flash', metavar='project', help='flash project to the device')
parser.add_argument('--verbose', help='verbose build', action='store_true')
parser.add_argument('--port', help='override port for flashing')
parser.add_argument('--list-projects', help='list available projects', action='store_true')

args = parser.parse_args()

projects = compute_targets()

if args.build_all:
    args.build = sorted(projects.keys())

if args.list_projects:
    print('\n'.join(sorted(projects.keys())))

if args.build:
    arduino = Arduino.get()
    for project_name in args.build:
        build_project(projects[project_name], args.verbose)

if args.flash:
    flash_project(projects[args.flash], args.verbose, args.port)


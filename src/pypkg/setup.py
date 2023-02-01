#!/usr/bin/env python

from setuptools import setup

setup(name = 'pyfe',
  version = '0.1',
  packages=['pyfe'],
	package_data={'pyfe': ['_pyfe.so']},
  include_package_data=True,
  install_requires=['numpy',],
)
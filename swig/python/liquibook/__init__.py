import sys
if sys.version_info.major >= 3:
    from .liquibook import *
    from .liquibook import _liquibook
else:
    from liquibook import *
    from liquibook import _liquibook
del sys

__author__ = 'Mike Kipnis'
__email__ = 'mike.kipnis@gmail.com'

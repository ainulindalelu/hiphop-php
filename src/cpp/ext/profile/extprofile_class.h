/*
   +----------------------------------------------------------------------+
   | HipHop for PHP                                                       |
   +----------------------------------------------------------------------+
   | Copyright (c) 2010 Facebook, Inc. (http://www.facebook.com)          |
   | Copyright (c) 1997-2010 The PHP Group                                |
   +----------------------------------------------------------------------+
   | This source file is subject to version 3.01 of the PHP license,      |
   | that is bundled with this package in the file LICENSE, and is        |
   | available through the world-wide-web at the following url:           |
   | http://www.php.net/license/3_01.txt                                  |
   | If you did not receive a copy of the PHP license and are unable to   |
   | obtain it through the world-wide-web, please send a note to          |
   | license@php.net so we can mail you a copy immediately.               |
   +----------------------------------------------------------------------+
*/

#ifndef __EXTPROFILE_CLASS_H__
#define __EXTPROFILE_CLASS_H__

// >>>>>> Generated by idl.php. Do NOT modify. <<<<<<

#include <cpp/ext/ext_class.h>

namespace HPHP {
///////////////////////////////////////////////////////////////////////////////

#ifndef PROFILE_BUILTIN
#define x_get_declared_classes f_get_declared_classes
#else
inline Array x_get_declared_classes() {
  FUNCTION_INJECTION(get_declared_classes);
  return f_get_declared_classes();
}
#endif

#ifndef PROFILE_BUILTIN
#define x_get_declared_interfaces f_get_declared_interfaces
#else
inline Array x_get_declared_interfaces() {
  FUNCTION_INJECTION(get_declared_interfaces);
  return f_get_declared_interfaces();
}
#endif

#ifndef PROFILE_BUILTIN
#define x_class_exists f_class_exists
#else
inline bool x_class_exists(CStrRef class_name, bool autoload = false) {
  FUNCTION_INJECTION(class_exists);
  return f_class_exists(class_name, autoload);
}
#endif

#ifndef PROFILE_BUILTIN
#define x_interface_exists f_interface_exists
#else
inline bool x_interface_exists(CStrRef interface_name, bool autoload = false) {
  FUNCTION_INJECTION(interface_exists);
  return f_interface_exists(interface_name, autoload);
}
#endif

#ifndef PROFILE_BUILTIN
#define x_get_class_methods f_get_class_methods
#else
inline Array x_get_class_methods(CVarRef class_or_object) {
  FUNCTION_INJECTION(get_class_methods);
  return f_get_class_methods(class_or_object);
}
#endif

#ifndef PROFILE_BUILTIN
#define x_get_class_vars f_get_class_vars
#else
inline Array x_get_class_vars(CStrRef class_name) {
  FUNCTION_INJECTION(get_class_vars);
  return f_get_class_vars(class_name);
}
#endif

#ifndef PROFILE_BUILTIN
#define x_get_class f_get_class
#else
inline Variant x_get_class(CVarRef object = null_variant) {
  FUNCTION_INJECTION(get_class);
  return f_get_class(object);
}
#endif

#ifndef PROFILE_BUILTIN
#define x_get_parent_class f_get_parent_class
#else
inline Variant x_get_parent_class(CVarRef object = null_variant) {
  FUNCTION_INJECTION(get_parent_class);
  return f_get_parent_class(object);
}
#endif

#ifndef PROFILE_BUILTIN
#define x_is_a f_is_a
#else
inline bool x_is_a(CObjRef object, CStrRef class_name) {
  FUNCTION_INJECTION(is_a);
  return f_is_a(object, class_name);
}
#endif

#ifndef PROFILE_BUILTIN
#define x_is_subclass_of f_is_subclass_of
#else
inline bool x_is_subclass_of(CVarRef class_or_object, CStrRef class_name) {
  FUNCTION_INJECTION(is_subclass_of);
  return f_is_subclass_of(class_or_object, class_name);
}
#endif

#ifndef PROFILE_BUILTIN
#define x_method_exists f_method_exists
#else
inline bool x_method_exists(CVarRef class_or_object, CStrRef method_name) {
  FUNCTION_INJECTION(method_exists);
  return f_method_exists(class_or_object, method_name);
}
#endif

#ifndef PROFILE_BUILTIN
#define x_property_exists f_property_exists
#else
inline bool x_property_exists(CVarRef class_or_object, CStrRef property) {
  FUNCTION_INJECTION(property_exists);
  return f_property_exists(class_or_object, property);
}
#endif

#ifndef PROFILE_BUILTIN
#define x_get_object_vars f_get_object_vars
#else
inline Array x_get_object_vars(CObjRef object) {
  FUNCTION_INJECTION(get_object_vars);
  return f_get_object_vars(object);
}
#endif

#ifndef PROFILE_BUILTIN
#define x_call_user_method_array f_call_user_method_array
#else
inline Variant x_call_user_method_array(CStrRef method_name, Variant obj, CArrRef paramarr) {
  FUNCTION_INJECTION(call_user_method_array);
  return f_call_user_method_array(method_name, ref(obj), paramarr);
}
#endif

#ifndef PROFILE_BUILTIN
#define x_call_user_method f_call_user_method
#else
inline Variant x_call_user_method(int _argc, CStrRef method_name, Variant obj, CArrRef _argv = null_array) {
  FUNCTION_INJECTION(call_user_method);
  return f_call_user_method(_argc, method_name, ref(obj), _argv);
}
#endif


///////////////////////////////////////////////////////////////////////////////
}

#endif // __EXTPROFILE_CLASS_H__

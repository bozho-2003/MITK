
# mitkFunctionCheckMitkCompatibility(VERSIONS [<version_name> <minimum_required_version>]... [REQUIRED])
#
# Example:
# mitkFunctionCheckMitkCompatibility(VERSIONS MITK_VERSION_PLUGIN_SYSTEM 1 REQUIRED)
#   
function(mitkFunctionCheckMitkCompatibility)

  macro_parse_arguments(_COMPAT "VERSIONS" "REQUIRED" ${ARGN})
  
  set(_is_version_name 1)
  foreach(_item ${_COMPAT_VERSIONS})
    if(_is_version_name)
      set(_is_version_name 0)
      set(_version_name ${_item})
      if (NOT ${_version_name})
        set(_msg_version_name_not_defined "Your MITK version is too old (${_version_name} not defined)")
        if(_COMPAT_REQUIRED)
          message(SEND_ERROR "${_msg_version_name_not_defined}")
        else()
          message(WARNING "${_msg_version_name_not_defined}")
        endif()
      endif()
    else()
      set(_is_version_name 1)
      if (${_version_name})
        set(_required_version ${_item})
        if(${_version_name} VERSION_LESS ${_required_version})
          set(_msg_version_mismatch "Your MITK version is too old, ${_version_name} version ${_required_version} or higher required, but only version ${${_version_name}} present.")
          if(${_version_name}_HASH)
            set(_msg_version_mismatch "${_msg_version_mismatch} Use Git hash ${${_version_name}_HASH} or newer.")
          endif()
          
          if(_COMPAT_REQUIRED)
            message(SEND_ERROR "${_msg_version_mismatch}")
          else()
            message(WARNING "${_msg_version_mismatch}")
          endif()
        endif()
      endif()
    endif()
  endforeach()

endfunction()

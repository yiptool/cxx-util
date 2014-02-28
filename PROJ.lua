
SUBPROJECT("cxx-util")

DEFINES {
	"ASSERT_H=\"" .. CURRENT_SOURCE_DIR .. "/assert.h\"",
	"LOGGER_H=\"" .. CURRENT_SOURCE_DIR .. "/logger.h\"",
	"MACROS_H=\"" .. CURRENT_SOURCE_DIR .. "/macros.h\"",
	"FMT_H=\"" .. CURRENT_SOURCE_DIR .. "/fmt.h\"",
	"TYPES_H=\"" .. CURRENT_SOURCE_DIR .. "/types.h\"",
	"UNORDERED_H=\"" .. CURRENT_SOURCE_DIR .. "/unordered.h\"",
	"REF_COUNTED_OBJECT_H=\"" .. CURRENT_SOURCE_DIR .. "/ref_counted_object.h\"",
	"WEAK_PTR_H=\"" .. CURRENT_SOURCE_DIR .. "/weak_ptr.h\"",
	"STRONG_PTR_H=\"" .. CURRENT_SOURCE_DIR .. "/strong_ptr.h\"",
}

SOURCE_FILES {
	"assert.cpp",
	"assert.h",
	"fmt.h",
	"logger.cpp",
	"logger.h",
	"macros.h",
	"ref_counted_object.cpp",
	"ref_counted_object.h",
	"strong_ptr.h",
	"types.h",
	"unordered.h",
	"weak_ptr.h"
}

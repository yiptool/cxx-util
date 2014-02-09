
SUBPROJECT("cxx-util")

DEFINES {
	"ASSERT_H=\"" .. CURRENT_SOURCE_DIR .. "/assert.h\"",
	"LOGGER_H=\"" .. CURRENT_SOURCE_DIR .. "/logger.h\"",
	"MACROS_H=\"" .. CURRENT_SOURCE_DIR .. "/macros.h\"",
	"FMT_H=\"" .. CURRENT_SOURCE_DIR .. "/fmt.h\"",
	"TYPES_H=\"" .. CURRENT_SOURCE_DIR .. "/types.h\"",
	"UNORDERED_H=\"" .. CURRENT_SOURCE_DIR .. "/unordered.h\"",
}

SOURCE_FILES {
	"assert.cpp",
	"assert.h",
	"fmt.h",
	"logger.cpp",
	"logger.h",
	"macros.h",
	"types.h",
	"unordered.h"
}

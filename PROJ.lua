
SUBPROJECT("cxx-util")

DEFINES {
	"ASSERT_H=\"" .. CURRENT_SOURCE_DIR .. "/assert.h\"",
	"LOGGER_H=\"" .. CURRENT_SOURCE_DIR .. "/logger.h\"",
}

SOURCE_FILES {
	"assert.cpp",
	"assert.h",
	"fmt.h",
	"logger.cpp",
	"logger.h",
	"macros.h",
}

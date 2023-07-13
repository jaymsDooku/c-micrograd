add_executable(${PROJECT_NAME} variable.h variable.c grad_function.h grad_function.c)
target_sources(${PROJECT_NAME} PRIVATE main.c)
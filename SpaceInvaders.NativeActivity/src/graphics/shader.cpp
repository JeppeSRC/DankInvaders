#include "shader.h"
#include <core/log.h>
#include <util/utils.h>

unsigned int Shader::activeShaderID = 0;
Shader* Shader::activeShader = nullptr;

static bool check_error(unsigned int shader, unsigned int param, bool isProgram) {
	int res = 1;
	char log[2048] = { 0 };
	if (isProgram) {
		glGetProgramiv(shader, param, &res);
		if (res == 0) {
			glGetProgramInfoLog(shader, 2048, 0, log);
			LOGE("Shader ERROR: %s", log);
			return true;
		}
	} else {
		glGetShaderiv(shader, param, &res);
		if (res == 0) {
			glGetShaderInfoLog(shader, 2048, 0, log);
			LOGD("Shader %s", log);
			return true;
		}
	}

	return false;
}

Shader::Shader(const char* vertex, const char* fragment) {
	LOGD("Compiling shader");
	unsigned int shader = glCreateProgram();

	unsigned int v = glCreateShader(GL_VERTEX_SHADER);
	unsigned int f = glCreateShader(GL_FRAGMENT_SHADER);

	LOGD("P: %u V: %u F: %u", shader, v, f);

	int vlen = (int)strlen(vertex);
	int flen = (int)strlen(fragment);

	glShaderSource(v, 1, &vertex, &vlen);
	glShaderSource(f, 1, &fragment, &flen);


	glCompileShader(v);
	if (check_error(v, GL_COMPILE_STATUS, false)) {
		LOGE("Failed to compile vertex shader");
		goto error;
	}

	glCompileShader(f);
	if (check_error(f, GL_COMPILE_STATUS, false)) {
		LOGE("Failed to compile fragment shader");
		goto error;
	}

	glAttachShader(shader, v);
	glAttachShader(shader, f);

	glLinkProgram(shader);
	if (check_error(shader, GL_LINK_STATUS, true)) {
		LOGE("Failed to link shader");
		goto error;
	}

	glValidateProgram(shader);
	if (check_error(shader, GL_VALIDATE_STATUS, true)) {
		LOGE("Failed to validate shader");
		goto error;
	}

	glDeleteShader(v);
	glDeleteShader(f);

	return;

error:
	glDeleteShader(v);
	glDeleteShader(f);
	glDeleteProgram(shader);
}

Shader::~Shader() {
	glDeleteProgram(shader);
}

void Shader::Bind() {
	if (shader != activeShaderID) {
		glUseProgram(shader);
		activeShaderID = shader;
	}
	activeShader = this;
}

unsigned int Shader::GetAttributeLocation(const char* name) {
	return glGetAttribLocation(shader, name);
}

unsigned int Shader::GetUniformLocation(const char* name) {
	unsigned int hash = hash_string(name);
	unsigned int loc = cache.Retrieve(hash);
	if (!loc) {
		loc = glGetUniformLocation(shader, name);
		cache.Add(hash, loc);
	}

	return loc;
}

void Shader::SetFloat(const char* name, float v) {
	SetFloat(GetUniformLocation(name), v);
}

void Shader::SetFloat(unsigned int location, float v) const {
	glUniform1f(location, v);
}

void Shader::SetVec2(const char* name, float x, float y) {
	SetVec2(GetUniformLocation(name), x, y);
}

void Shader::SetVec2(unsigned int location, float x, float y) const {
	glUniform2f(location, x, y);
}

void Shader::SetVec3(const char* name, float x, float y, float z) {
	SetVec3(GetUniformLocation(name), x, y, z);
}

void Shader::SetVec3(unsigned int location, float x, float y, float z) const {
	glUniform3f(location, x, y, z);
}

void Shader::SetVec4(const char* name, float x, float y, float z, float w) {
	SetVec4(GetUniformLocation(name), x, y, z, w);
}

void Shader::SetVec4(unsigned int location, float x, float y, float z, float w) const {
	glUniform4f(location, x, y, z, w);
}

void Shader::SetMat4(const char* name, float* data) {
	SetMat4(GetUniformLocation(name), data);
}

void Shader::SetMat4(unsigned int location, float* data) const {
	glUniformMatrix4fv(location, 1, false, data);
}

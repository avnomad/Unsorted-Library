#include "shader loader.h"

#include <iostream>
using std::cout;
using std::cin;
using std::endl;
using std::cerr;
using std::clog;
using std::left;

#include <fstream>
using std::ifstream;
using std::ofstream;
using std::fstream;
using std::ios;

#include <iomanip>
using std::setw;
using std::setprecision;

#include <algorithm>
using std::copy;

#include <string>
using std::string;

#include <iterator>
using std::back_inserter;

#include <char reader.h>



GLuint load_shader_program(const char *vertex_file,const char *fragment_file)
{
	ifstream in;
	string source;
	const char *s;

	GLint compile_status,log_length,link_status,validate_status;
	GLuint vertex_shader, fragment_shader;
	GLuint program;

	// prepare cout for printing.
	cout << std::left << std::setfill('.');

	// read the file (vertex shader) into memory and convert it to C string.
	in.open(vertex_file);
	copy(CharReader(in),CharReader(),back_inserter(source));
	s = source.c_str();

	// compile vertex shader.
	cout << "\n    Vertex shader\n";
	cout << setw(35) << "Creating shader object";
	if(vertex_shader = glCreateShader(GL_VERTEX_SHADER))
		cout << "done\n";
	else
		cout << "failed\n";

	cout << setw(35) << "Associating source code";
	glShaderSource(vertex_shader,1,&s,NULL);
	cout << "done\n";

	cout << setw(35) << "Compiling shader";
	glCompileShader(vertex_shader);
	glGetShaderiv(vertex_shader,GL_COMPILE_STATUS,&compile_status);
	glGetShaderiv(vertex_shader,GL_INFO_LOG_LENGTH,&log_length);
	s = new char[log_length];
	glGetShaderInfoLog(vertex_shader,log_length,NULL,(char*)s);
	if(compile_status == GL_TRUE)
		cout << "done\n";
	else
		cout << "failed\n";
	cout << '\n' << s << '\n';
	delete[] s;

	// clean up file and string objects.
	in.close();
	in.clear();
	source.clear();

	// read the file (fragment shader) into memory and convert it to C string.
	in.open(fragment_file);
	copy(CharReader(in),CharReader(),back_inserter(source));
	s = source.c_str();

	// compile fragment shader.
	cout << "\n    Fragment shader\n";
	cout << setw(35) << "Creating shader object";
	if(fragment_shader = glCreateShader(GL_FRAGMENT_SHADER))
		cout << "done\n";
	else
		cout << "failed\n";

	cout << setw(35) << "Associating source code";
	glShaderSource(fragment_shader,1,&s,NULL);
	cout << "done\n";

	cout << setw(35) << "Compiling shader";
	glCompileShader(fragment_shader);
	glGetShaderiv(fragment_shader,GL_COMPILE_STATUS,&compile_status);
	glGetShaderiv(fragment_shader,GL_INFO_LOG_LENGTH,&log_length);
	s = new char[log_length];
	glGetShaderInfoLog(fragment_shader,log_length,NULL,(char*)s);
	if(compile_status == GL_TRUE)
		cout << "done\n";
	else
		cout << "failed\n";
	cout << '\n' << s << '\n';
	delete[] s;

	// link shader program.
	cout << '\n' << setw(35) << "Creating shader program";
	if(program = glCreateProgram())
		cout << "done\n";
	else
		cout << "failed\n";

	cout << setw(35) << "Attaching vertex shader object";
	glAttachShader(program,vertex_shader);
	cout << "done\n";

	cout << setw(35) << "Attaching fragment shader object";
	glAttachShader(program,fragment_shader);
	cout << "done\n";

	cout << setw(35) << "Linking shader program";
	glLinkProgram(program);
	glGetProgramiv(program,GL_LINK_STATUS,&link_status);
	glGetProgramiv(program,GL_INFO_LOG_LENGTH,&log_length);
	s = new char[log_length];
	glGetProgramInfoLog(program,log_length,NULL,(char*)s);
	if(link_status == GL_TRUE)
		cout << "done\n";
	else
		cout << "failed\n";
	cout << '\n' << s << '\n';
	delete[] s;

	cout << setw(35) << "Validating shader program";
	glValidateProgram(program);
	glGetProgramiv(program,GL_VALIDATE_STATUS,&validate_status);
	glGetProgramiv(program,GL_INFO_LOG_LENGTH,&log_length);
	s = new char[log_length];
	glGetProgramInfoLog(program,log_length,NULL,(char*)s);
	if(validate_status == GL_TRUE)
		cout << "done\n";
	else
		cout << "failed\n";
	cout << '\n' << s << '\n';
	delete[] s;

	// return the linked program.
	return program;
} // end function load_shaders
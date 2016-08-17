#include "InputClass.h"
#include <cstring>

InputClass::InputClass()
{
}

InputClass::InputClass(const InputClass&) {

}


InputClass::~InputClass()
{
}

void InputClass::Initialize() {
	::memset((void*)m_keys, 0, 256);
	return;
}

void InputClass::KeyDown(unsigned int key) {
	m_keys[key] = true;
	return;
}

void InputClass::KeyUp(unsigned int key) {
	m_keys[key] = false;
	return;
}

bool InputClass::IsKeyDown(unsigned int key) {
	return m_keys[key];
}



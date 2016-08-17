#ifndef __INPUTCLASS__
#define  __INPUTCLASS__
class InputClass
{
public:
	InputClass();
	InputClass(const InputClass&);
	~InputClass();

	void Initialize();

	void KeyDown(unsigned int);
	void KeyUp(unsigned init);

	bool IsKeyDown(unsigned int);

private:
	bool m_keys[256];
};
#endif


#pragma once

class TInputLayout
{
public:
	TInputLayout(void);
	~TInputLayout(void);
	int CreateInputLayout();
	void Release();

private:
	ID3D11InputLayout* VertexLayout;
};




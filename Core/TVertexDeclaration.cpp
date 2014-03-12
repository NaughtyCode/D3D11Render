#include "stdafx.h"
#include "Core.h"


TVertexDeclaration::TVertexDeclaration(const TVertexElementArray& Elements)
{
	UINT Index = 0;
	for(Index;Index < Elements.size();Index++)
	{
		const TVertexElement& Element = Elements[Index];
		D3D11_INPUT_ELEMENT_DESC D3DElement;
		D3DElement.InputSlot = Element.StreamIndex;
		D3DElement.AlignedByteOffset = Element.Offset;
		
		switch(Element.Type)
		{
			case ELEMENTTYPE_FLOAT1:
				D3DElement.Format = DXGI_FORMAT_R32_FLOAT;
				break;
			case ELEMENTTYPE_FLOAT2:
				D3DElement.Format = DXGI_FORMAT_R32G32_FLOAT;
				break;
			case ELEMENTTYPE_FLOAT3:
				D3DElement.Format = DXGI_FORMAT_R32G32B32_FLOAT;
				break;
			case ELEMENTTYPE_FLOAT4:
				D3DElement.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
				break;
			case ELEMENTTYPE_PACKEDNORMAL:
				D3DElement.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
				break;
			case ELEMENTTYPE_UBYTE4:
				D3DElement.Format = DXGI_FORMAT_R8G8B8A8_UINT;
				break;
			case ELEMENTTYPE_UBYTE4N:
				D3DElement.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
				break;
			case ELEMENTTYPE_COLOR:
				D3DElement.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
				break;
			case ELEMENTTYPE_SHORT2:
				D3DElement.Format = DXGI_FORMAT_R16G16_SINT;
				break;
			case ELEMENTTYPE_SHORTN:
				D3DElement.Format = DXGI_FORMAT_R16G16_SNORM;
				break;
			case ELEMENTTYPE_HALF2:
				D3DElement.Format = DXGI_FORMAT_R16G16_FLOAT;
				break;
			default:
				printf("UnKnown vertex element type(%u)",Elements[Index].Type);
		};
		
		switch(Element.Usage)
		{
			case SEMANTICNAME_POSITION:
				D3DElement.SemanticName = "POSITION";
				break;
			case SEMANTICNAME_TEXTURECOORDINATE:
				D3DElement.SemanticName = "TEXCOORD";
				break;
			case SEMANTICNAME_BLENDWEIGHT:
				D3DElement.SemanticName = "BLENDWEIGHT";
				break;
			case SEMANTICNAME_BLENDINDICES:
				D3DElement.SemanticName = "BLENDINDICES";
				break;
			case SEMANTICNAME_NORMAL:
				D3DElement.SemanticName = "NORMAL";
				break;
			case SEMANTICNAME_TANGENT:
				D3DElement.SemanticName = "TANGENT";
				break;
			case SEMANTICNAME_BINORMAL:
				D3DElement.SemanticName = "BINORMAL";
				break;
			case SEMANTICNAME_COLOR:
				D3DElement.SemanticName = "COLOR";
				break;
		};
		
		D3DElement.SemanticIndex = Element.UsageIndex;
		D3DElement.InputSlotClass = Element.bUseInstanceIndex ? D3D11_INPUT_PER_INSTANCE_DATA : D3D11_INPUT_PER_VERTEX_DATA;
		D3DElement.InstanceDataStepRate = Element.bUseInstanceIndex ? 1 : 0;
		ElemetArray[Index]=D3DElement;
	}
	
}





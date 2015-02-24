#include <PrecompiledHeader.h>
#include <ITPMeshImporter.h>
#include <ticpp.h>

namespace ITP485
{
	struct PackedVector3
	{
		float mX, mY, mZ;
	};

	struct PackedVector2
	{
		float mX, mY;
	};

	struct PackedVector4
	{
		float mX, mY, mZ, mW;
	};

	// Position and texture coordinates
	struct VERTEX_P_T
	{
		PackedVector3 mPos;
		PackedVector2 mUV;
	};

	// Position, normal, and texture coordinates
	struct VERTEX_P_N_T
	{
		PackedVector3 mPos;
		PackedVector3 mNormal;
		PackedVector2 mUV;
	};

	// Position, normal, skinning weights, skinning indices, and texture coordinates
	struct VERTEX_P_N_S_T
	{
		PackedVector3 mPos;
		PackedVector3 mNormal;
		PackedVector4 mWeights;
		PackedVector4 mIndices;
		PackedVector2 mUV;
	};

	MeshPtr ITPMeshImporter::ImportMesh( const char* inFileName )
	{
		int vertSize = 0;
		int vertexCount;
		int triangleCount;
		vector< uint16_t > indices;
		vector< float > vertices;	//we use a vector of floats because we don't know how many floats there will be per vertex, but we do know they're all floats!
		string inputLayoutName;

		// Parse the itpmesh file
		ticpp::Document doc( inFileName  );
		doc.LoadFile();

		// This is some really ugly XML parsing code
		ticpp::Iterator<ticpp::Element> child;
		for(child = child.begin(doc.FirstChildElement()); child != child.end(); child++)
		{
			// The value of this child identifies the name of this element
			std::string strName;
			std::string strValue;
			std::string strText;

			child->GetValue( &strName );
			if (strName == "format")
			{
				// Select the correct vertex format
				inputLayoutName = child->GetText();
				if( inputLayoutName == "pt" )
				{
					vertSize = sizeof( VERTEX_P_T );
				}
				else if( inputLayoutName == "pnt" )
				{
					vertSize = sizeof( VERTEX_P_N_T );
				}
				else if( inputLayoutName == "pnst" )
				{
					vertSize = sizeof( VERTEX_P_N_S_T );
				}			
			}
			else if (strName == "texture")
			{
				/*
				// Load the texture
				strText = child->GetText();
				hr = D3DXCreateTextureFromFileA(pDevice, strText.c_str(), &m_pTexture);
				Dbg_Assert(hr == D3D_OK, "Could not load texture!");
				*/
			}
			else if( strName == "triangles" )
			{
				// Initialize index buffer memory
				strValue = child->GetAttribute( "count" );
			
				triangleCount = atoi( strValue.c_str() );
				indices.resize( triangleCount * 3 );
				uint16_t* index = indices.data();

				// Now get every triangle
 				ticpp::Iterator<ticpp::Element> tri;
				for( tri = tri.begin( child.Get() ); tri != tri.end(); tri++ )
 				{
					short v0, v1, v2;
 					sscanf_s( tri->GetText().c_str(), "%hd,%hd,%hd", &v0, &v1, &v2);
				
					*index++ = v0;
					*index++ = v1;
					*index++ = v2;
 				}

			}
			else if (strName == "vertices")
			{
				strValue = child->GetAttribute( "count" );
				vertexCount = atoi( strValue.c_str() );
				vertices.resize( vertexCount * vertSize / sizeof( float ) );
				float* vertex = vertices.data();
			
				// Now get every vertex
				ticpp::Iterator<ticpp::Element> vert;
				for(vert = vert.begin(child.Get()); vert != vert.end(); vert++)
				{
					float x, y, z, w;

					// Get every element of this vertex
					ticpp::Iterator<ticpp::Element> ele;
					for(ele = ele.begin(vert.Get()); ele != ele.end(); ele++)
					{
						//this code requires all the data be in order. a little weird, but the itp mesh format guarantees this, luckily
						ele->GetValue(&strName);
						if ( strName == "pos" )
						{
							sscanf_s(ele->GetText().c_str(), "%f,%f,%f", &x, &y, &z);
							*vertex++ = x;
							*vertex++ = y;
							*vertex++ = z;
						}
						else if (strName == "norm")
						{
							sscanf_s(ele->GetText().c_str(), "%f,%f,%f", &x, &y, &z);
							*vertex++ = x;
							*vertex++ = y;
							*vertex++ = z;					
						}
						else if (strName == "tex")
						{
							sscanf_s(ele->GetText().c_str(), "%f,%f", &x, &y);
							*vertex++ = x;
							*vertex++ = y;
						}
						else if (strName == "sw")
						{
							sscanf_s(ele->GetText().c_str(), "%f,%f,%f,%f", &x, &y, &z, &w);
							*vertex++ = x;
							*vertex++ = y;
							*vertex++ = z;
							*vertex++ = w;
						}
						else if (strName == "si")
						{
							sscanf_s(ele->GetText().c_str(), "%f,%f,%f,%f", &x, &y, &z, &w);
							*vertex++ = x;
							*vertex++ = y;
							*vertex++ = z;
							*vertex++ = w;
						}
					}
				}

			}
		}

		return std::make_shared< Mesh >( inFileName, vertices.data(), vertexCount, 
										 vertSize, inputLayoutName, 
										 indices.data(), indices.size() );
	}

/*
void MeshData::Draw(ID3DXEffect* pEffect, D3DXHANDLE hTechnique)
{
	pEffect->SetTexture("DiffuseMapTexture", m_pTexture);

	if (SUCCEEDED(pEffect->SetTechnique(hTechnique)))
	{
		UINT iPasses;
		if (SUCCEEDED(pEffect->Begin(&iPasses, 0)))
		{
			for (UINT pass = 0; pass < iPasses; ++pass)
			{
				if (SUCCEEDED(pEffect->BeginPass(pass)))
				{
					// DRAW THE MESH!
					LPDIRECT3DDEVICE9 pDevice = GraphicsDevice::get().GetD3DDevice();
					pDevice->SetVertexDeclaration(m_pVertexDecl);
					pDevice->SetStreamSource(0,m_pVertexBuffer,0,m_iVertexSize);
					pDevice->SetIndices(m_pIndexBuffer);
					pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST,0,0,m_iNumVerts,0,m_iNumTris);
					
					pEffect->EndPass();
				}
			}

			pEffect->End();
		}
	}
}
*/
} // namespace

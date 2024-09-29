#include "SSurface.h"

struct SSurface::Data
{
	SVertex *vertices;
	uint32_t vertexCnt;
	SByteArrayPtr byteArrayPtr;
};


SSurface::SSurface(uint32_t vertexCnt)
	:d_(new Data())
{
	d_->byteArrayPtr = new SByteArray(SVertex::GetVertexSize() * vertexCnt);
	d_->vertices = new SVertex[vertexCnt];
	d_->vertexCnt = vertexCnt;


}

SSurface::~SSurface()
{
	d_->byteArrayPtr = nullptr;

	delete[] d_->vertices;
	d_->vertexCnt = 0;

	delete d_;
}

uint32_t SSurface::getVertexCnt()
{
	return d_->vertexCnt;
}

void SSurface::setVertex(uint32_t index, const SVertex& vertex)
{
	if (index < d_->vertexCnt)
	{
		d_->vertices[index] = vertex;
	}
}

SByteArrayPtr SSurface::toByteArrayPtr()
{
	for (int i = 0; i < d_->vertexCnt; i++)
	{
		const SVertex &vertex = d_->vertices[i];
		SPointF3D screenPos = vertex.getScreenPos();
		d_->byteArrayPtr->writeData(i * SVertex::GetVertexSize(), &screenPos, sizeof(SPointF3D));
	}

	return d_->byteArrayPtr;
}

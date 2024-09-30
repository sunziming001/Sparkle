#include "SSurface.h"

struct SSurface::Data
{
	SVertex *vertices;
	uint32_t* vertexDrawOrder;

	uint32_t vertexCnt;
	SByteArrayPtr byteArrayPtr;
};


SSurface::SSurface(uint32_t vertexCnt)
	:d_(new Data())
{
	uint32_t triangleCnt = (vertexCnt - 2);
	d_->byteArrayPtr = new SByteArray(SVertex::GetVertexSize() * vertexCnt);
	d_->vertices = new SVertex[vertexCnt];
	d_->vertexCnt = vertexCnt;

	d_->vertexDrawOrder = new uint32_t[triangleCnt*3];
	for (uint32_t i = 0; i < triangleCnt; i++)
	{
		uint32_t startIndex = 3 * i;
		d_->vertexDrawOrder[startIndex] = 0;
		d_->vertexDrawOrder[startIndex + 1] =i+1;
		d_->vertexDrawOrder[startIndex + 2] = i + 2;
	}
}

SSurface::~SSurface()
{
	d_->byteArrayPtr = nullptr;

	delete[] d_->vertexDrawOrder;

	delete[] d_->vertices;
	d_->vertexCnt = 0;

	delete d_;
}

uint32_t SSurface::getVertexCnt()
{
	return d_->vertexCnt;
}

uint32_t SSurface::getTriangleCnt()const
{
	return d_->vertexCnt - 2;
}

const uint32_t* SSurface::getVertexDrawOrder()const
{
	return d_->vertexDrawOrder;
}

size_t SSurface::getVertexDrawOrderSize() const
{
	return sizeof(uint32_t) * 3 * getTriangleCnt();
}

size_t SSurface::getVertexDrawOrderCnt() const
{
	return 3* getTriangleCnt();
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
	for (uint32_t i = 0; i < d_->vertexCnt; i++)
	{
		const SVertex &vertex = d_->vertices[i];
		SPointF3D screenPos = vertex.getScreenPos();
		d_->byteArrayPtr->writeData(i * SVertex::GetVertexSize(), &screenPos, sizeof(SPointF3D));
	}

	return d_->byteArrayPtr;
}

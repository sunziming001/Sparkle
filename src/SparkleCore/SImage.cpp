#include "SImage.h"
#include "SpkFileHelper.h"
#include "stb_image.h"

struct SImage::Data
{
	SByteArray imgData;
	SSize2D imgSize = {0,0};
	uint32_t channels=0;
};


SImage::SImage()
	:d_(new Data())
{

}

SImage::~SImage()
{
	delete d_;
}

SSize2D SImage::getImageSize()const
{
	return d_->imgSize;
}

uint32_t SImage::getImageWidth() const
{
	return d_->imgSize.w;
}

uint32_t SImage::getImageHeight() const
{
	return d_->imgSize.h;
}

uint32_t SImage::getChannels()const
{
	return d_->channels;
}

void SImage::loadFromResPack(const SString& path)
{
	SByteArray rawData = SpkFileHelper::getInstance()->getRes(path);
	int channels = 0;
	int w = 0;
	int h = 0;
	stbi_uc* buff = stbi_load_from_memory(
		rawData.data(),
		rawData.size(),
		&w,
		&h,
		&(channels),
		0);
	
	d_->channels = static_cast<uint32_t>(channels);
	d_->imgSize.w = w;
	d_->imgSize.h = h;
	
	d_->imgData = SByteArray(buff, w * h * channels);



	stbi_image_free(buff);
}

unsigned char* SImage::getDataPtr() const
{
	return d_->imgData.data();
}

size_t SImage::getDataSize() const
{
	return d_->imgData.size();
}

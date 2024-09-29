#include "SKeyEvent.h"

struct SKeyEvent::Data
{
	SKeyType type;
	SKeyEnum key;
	SKeyStatus status;
	SFlags<SKeyModifier> modifiers;
};

SKeyEvent::SKeyEvent(
	SKeyType type,
	SKeyEnum key, 
	SKeyStatus status,
	SFlags<SKeyModifier> modifiers)
		:SEvent(SEventType::Key)
		,d_(new Data())
	
{
	d_->type = type;
	d_->key = key;
	d_->status = status;
	d_->modifiers = modifiers;
}

SKeyEvent::~SKeyEvent()
{
	delete d_;
}

SKeyEnum SKeyEvent::getKeyEnum() const
{
	return d_->key;
}

SFlags<SKeyModifier> SKeyEvent::getModifiers() const
{
	return d_->modifiers;
}

SKeyStatus SKeyEvent::getStatus() const
{
	return d_->status;
}

SKeyType SKeyEvent::getType() const
{
	return d_->type;
}

SStringPtr SKeyEvent::toLogString() const
{
	SStringPtr ret = SEvent::toLogString();
	(*ret) << SWS("{");
	(*ret) << "type: " << static_cast<uint32_t>(d_->type) << ";";
	(*ret) << "key: " << static_cast<uint32_t>(d_->key) << ";";
	(*ret) << "status: " << static_cast<uint32_t>(d_->status) << ";";
	(*ret) << "modifiers: " << static_cast<uint32_t>(d_->modifiers.getValue()) << ";";
	
	(*ret) << SWS("}");

	return ret;
}

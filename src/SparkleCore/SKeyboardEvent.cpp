#include "SKeyboardEvent.h"

struct SKeyboardEvent::Data
{
	SKeyboardKey key;
	SKeyboardStatus status;
	SFlags<SKeyboardModifier> modifiers;
};

SKeyboardEvent::SKeyboardEvent(
	SKeyboardKey key, 
	SKeyboardStatus status,
	SFlags<SKeyboardModifier> modifiers)
		:SEvent(SEventType::Keyboard)
		,d_(new Data())
	
{
	d_->key = key;
	d_->status = status;
	d_->modifiers = modifiers;
}

SKeyboardEvent::~SKeyboardEvent()
{
	delete d_;
}

SKeyboardKey SKeyboardEvent::getKey() const
{
	return d_->key;
}

SFlags<SKeyboardModifier> SKeyboardEvent::getModifiers() const
{
	return d_->modifiers;
}

SKeyboardStatus SKeyboardEvent::getStatus() const
{
	return d_->status;
}

SStringPtr SKeyboardEvent::toLogString() const
{
	SStringPtr ret = SEvent::toLogString();
	(*ret) << SWS("{");
	(*ret) << "key: " << static_cast<uint32_t>(d_->key) << ";";
	(*ret) << "status: " << static_cast<uint32_t>(d_->status) << ";";
	(*ret) << "modifiers: " << static_cast<uint32_t>(d_->modifiers.getValue()) << ";";
	
	(*ret) << SWS("}");

	return ret;
}

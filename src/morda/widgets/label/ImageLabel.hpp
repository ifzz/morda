#pragma once

#include "../core/Widget.hpp"

#include "../BlendWidget.hpp"

#include "../../resources/ResImage.hpp"


namespace morda{

/**
 * @brief Image widget.
 * This widget can display an image.
 * From GUI script it can be instantiated as "ImageLabel".
 * 
 * @param image - image resource.
 * @param keepAspectRatio - try to keep aspect ratio of the image when scaling.
 * @param repeatX - replicate image horizontally if size of the widget is bigger than size of the image resource.
 * @param repeatY - replicate image vertically if size of the widget is bigger than size of the image resource.
 */
class ImageLabel :
		public virtual Widget,
		public BlendWidget
{
	ImageLabel(const ImageLabel&);
	ImageLabel& operator=(const ImageLabel&);
	
	std::shared_ptr<const morda::ResImage> img;
	
	mutable std::shared_ptr<const morda::ResImage::QuadTexture> scaledImage;
	
	bool keepAspectRatio;
	
	kolme::Vec2b repeat_v;
	mutable std::array<kolme::Vec2f, 4> texCoords;
	
public:
	ImageLabel(const stob::Node* chain = nullptr);
public:
	virtual ~ImageLabel()noexcept{}
	
	void render(const morda::Matr4r& matrix)const override;

	morda::Vec2r measure(const morda::Vec2r& quotum)const override;
	
	void setImage(const std::shared_ptr<const ResImage>& image);
	
	void onResize() override;
	
	const decltype(repeat_v)& repeat()const noexcept{
		return this->repeat_v;
	}
	
	void setRepeat(decltype(repeat_v) r){
		this->repeat_v = r;
		this->scaledImage.reset();
	}
	
	void setKeepAspectRatio(bool keepAspectRatio){
		this->keepAspectRatio = keepAspectRatio;
		this->setRelayoutNeeded();
	}
private:

};

}

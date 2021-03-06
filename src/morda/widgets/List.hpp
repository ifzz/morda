#pragma once

#include "core/Widget.hpp"
#include "core/container/Container.hpp"


namespace morda{

/**
 * @brief Scrollable list widget.
 * This is a base class for vertical and horizontal lists.
 */
//TODO: list could be implemented based on ScrollArea and LinearContainer inside of it, for easier widgets arrangement when scrolling
class List : public Container{
	size_t addedIndex = size_t(-1);
	
	size_t posIndex = 0;
	real posOffset = real(0);
	
	bool isVertical;
	
	size_t numTailItems = 0;//Zero means that number of tail items has to be recomputed
	size_t firstTailItemIndex = 0;
	real firstTailItemOffset = real(0);
	
	
protected:
	List(bool isVertical, const stob::Node* chain);
public:
	List(const List&) = delete;
	List& operator=(const List&) = delete;
	
	/**
	 * @brief List items provider.
	 * User should subclass this class to provide items to the list.
	 */
	class ItemsProvider : virtual public utki::Shared{
		friend class List;
		
		List* list = nullptr;
	protected:
		ItemsProvider(){}
	public:
		/**
		 * @brief Get total number of items in the list.
		 * @return Number of items in the list.
		 */
		virtual size_t count()const noexcept = 0;
		
		/**
		 * @brief Get widget for item.
		 * @param index - index of item to get widget for.
		 * @return Widget for the requested item.
		 */
		virtual std::shared_ptr<Widget> getWidget(size_t index) = 0;
		
		/**
		 * @brief Recycle widget of item.
		 * @param index - index of item to recycle widget of.
		 * @param w - widget to recycle.
		 */
		virtual void recycle(size_t index, std::shared_ptr<Widget> w){}
		
		void notifyDataSetChanged();
	};
	
	void setItemsProvider(std::shared_ptr<ItemsProvider> provider = nullptr);
	

	void layOut()override;
	
	morda::Vec2r measure(const morda::Vec2r& quotum) const override;

	
	/**
	 * @brief Get number of items currently visible.
	 * @return Number of items which are currently visible, i.e. are not completely out of List's boundaries.
	 */
	size_t visibleCount()const{
		return this->children().size();
	}
	
	/**
	 * @brief Set scroll position as factor from [0:1].
	 * @param factor - factor of the scroll position to set.
	 */
	void setScrollPosAsFactor(real factor);
	
	/**
	 * @brief Get scroll factor.
	 * @return Current scroll position as factor from [0:1].
	 */
	real scrollFactor()const noexcept;
	
	/**
	 * @brief Data set changed signal.
	 * Emitted when list widget contents have actually been updated due to change in provider's model data set.
	 */
	std::function<void(List&)> dataSetChanged;
	
private:
	std::shared_ptr<ItemsProvider> provider;
	
	void updateChildrenList();
	
	bool arrangeWidget(std::shared_ptr<Widget>& w, real& pos, bool add, size_t index, T_ChildrenList::const_iterator insertBefore);//returns true if it was the last visible widget
	
	void updateTailItemsInfo();
	
	void handleDataSetChanged();
};


/**
 * @brief Horizontal list widget.
 * From GUI script it can be instantiated as "HorizontalList".
 */
class HorizontalList : public List{
public:
	HorizontalList(const stob::Node* chain = nullptr) :
			Widget(chain),
			List(false, chain)
	{}
	
	HorizontalList(const HorizontalList&) = delete;
	HorizontalList& operator=(const HorizontalList&) = delete;
};

/**
 * @brief Vertical list widget.
 * From GUI script it can be instantiated as "VerticalList".
 */
class VerticalList : public List{
public:
	VerticalList(const stob::Node* chain = nullptr) :
			Widget(chain),
			List(true, chain)
	{}
	
	VerticalList(const VerticalList&) = delete;
	VerticalList& operator=(const VerticalList&) = delete;
};

}

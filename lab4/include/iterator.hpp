#ifndef __ITERATOR_HPP__
#define __ITERATOR_HPP__

#include <boost/iterator/iterator_adaptor.hpp>
#include <iterator>

template<class Iterator>
class image_iterator
    : public boost::iterator_adaptor<
          image_iterator<Iterator>,
          Iterator,
          typename std::iterator_traits<Iterator>::value_type,
          boost::random_access_traversal_tag,
          typename std::iterator_traits<Iterator>::reference,
          typename std::iterator_traits<Iterator>::difference_type>
{
public:
    // ✅ То, что требует std::iterator_traits
    using value_type        = typename std::iterator_traits<Iterator>::value_type;
    using reference         = typename std::iterator_traits<Iterator>::reference;
    using difference_type   = typename std::iterator_traits<Iterator>::difference_type;
    using iterator_category = std::random_access_iterator_tag;

    image_iterator() = default;

    image_iterator(Iterator it, size_t width, size_t stride)
        : image_iterator::iterator_adaptor_(it),
          base_begin_(it),
          width_(width),
          stride_(stride)
    {}

private:
    friend class boost::iterator_core_access;

    Iterator base_begin_;
    size_t width_ = 0;
    size_t stride_ = 0;

    void increment() { advance(1); }
    void decrement() { advance(-1); }

    void advance(difference_type n)
    {
        if (n == 0) return;

        difference_type phys =
            std::distance(base_begin_, this->base_reference());

        difference_type row = phys / static_cast<difference_type>(stride_);
        difference_type col = phys % static_cast<difference_type>(stride_);
        difference_type logical =
            row * static_cast<difference_type>(width_) + col;

        logical += n;

        row = logical / static_cast<difference_type>(width_);
        col = logical % static_cast<difference_type>(width_);

        difference_type new_phys =
            row * static_cast<difference_type>(stride_) + col;

        this->base_reference() = base_begin_ + new_phys;
    }

    difference_type distance_to(const image_iterator& other) const
    {
        difference_type phys1 =
            std::distance(base_begin_, this->base_reference());
        difference_type phys2 =
            std::distance(base_begin_, other.base_reference());

        difference_type row1 = phys1 / static_cast<difference_type>(stride_);
        difference_type col1 = phys1 % static_cast<difference_type>(stride_);
        difference_type row2 = phys2 / static_cast<difference_type>(stride_);
        difference_type col2 = phys2 % static_cast<difference_type>(stride_);

        difference_type logical1 =
            row1 * static_cast<difference_type>(width_) + col1;
        difference_type logical2 =
            row2 * static_cast<difference_type>(width_) + col2;

        return logical2 - logical1;
    }
};

#endif // __ITERATOR_HPP__

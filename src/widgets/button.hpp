/*
	Copyright (C) 2003 - 2025
	by David White <dave@whitevine.net>
	Part of the Battle for Wesnoth Project https://www.wesnoth.org/

	This program is free software; you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation; either version 2 of the License, or
	(at your option) any later version.
	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY.

	See the COPYING file for more details.
*/

#pragma once

#include "widget.hpp"

#include "exceptions.hpp"

#include "sdl/texture.hpp"

namespace gui {

class button : public widget
{
public:
	enum TYPE { TYPE_PRESS, TYPE_CHECK, TYPE_TURBO, TYPE_IMAGE, TYPE_RADIO };
	TYPE get_type() const { return type_; }

	enum SPACE_CONSUMPTION { DEFAULT_SPACE, MINIMUM_SPACE };

	button(const std::string& label, TYPE type=TYPE_PRESS,
	       const std::string& button_image="", SPACE_CONSUMPTION spacing=DEFAULT_SPACE,
	       const bool auto_join=true, std::string overlay_image="", int font_size = -1);


	/** Default implementation, but defined out-of-line for efficiency reasons. */
	virtual ~button();
	void set_check(bool check);
	void set_active(bool active);
	bool checked() const;

	void set_label(const std::string& val);
	void set_image(const std::string& image_file_base);
	void set_overlay(const std::string& image_file_base);
	void set_image_path_suffix(const std::string& suffix) { button_image_path_suffix_ = suffix; load_images(); }

	bool pressed();
	bool hit(int x, int y) const;
	virtual void enable(bool new_val=true);
	void release();

protected:
	virtual void handle_event(const SDL_Event& event);
	virtual void mouse_motion(const SDL_MouseMotionEvent& event);
	virtual void mouse_down(const SDL_MouseButtonEvent& event);
	virtual void mouse_up(const SDL_MouseButtonEvent& event);
	virtual void draw_contents();

	TYPE type_;

private:

	void load_images();

	void calculate_size();

	std::string label_text_;

	texture image_, pressedImage_, activeImage_, pressedActiveImage_,
		touchedImage_, disabledImage_, pressedDisabledImage_,
		overlayImage_, overlayPressedImage_, overlayPressedDisabledImage_, overlayDisabledImage_,
		overlayActiveImage_;
	rect textRect_;

	enum STATE { UNINIT, NORMAL, ACTIVE, PRESSED, PRESSED_ACTIVE, TOUCHED_NORMAL, TOUCHED_PRESSED };
	STATE state_;

	bool pressed_;

	SPACE_CONSUMPTION spacing_;

	int base_height_, base_width_;

	std::string button_image_name_;
	std::string button_overlay_image_name_;
	std::string button_image_path_suffix_;

	int font_size_;
	int horizontal_padding_;
	int checkbox_horizontal_padding_;
	int vertical_padding_;

}; //end class button

}

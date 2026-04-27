#include "rend.h"

void	clean_rend(t_rend *rend);
void	button_press(t_rend *rend, float x, float y);
void	reset_progress(t_rend *rend);

int handle_input(t_rend *rend, XEvent xev)
{
	if (xev.type == KeyPress)
	{
		KeySym ks = XLookupKeysym(&xev.xkey, 0);
		if (ks == XK_Escape)
		{
			clean_rend(rend);
			return (1);
		}
		else if (ks == XK_space)
			rend->input.pause = !rend->input.pause;
		else if (ks == XK_Right)
		{
			if (rend->input.speed < 1.0)
				rend->input.speed = 1;
			else
				rend->input.speed = 2.0;
		}
		else if (ks == XK_Left)
		{
			if (rend->input.speed > 1.0)
				rend->input.speed = 1;
			else
				rend->input.speed = 0.5;
		}
		else if (ks == XK_u)
			rend->input.view_unused = !rend->input.view_unused;
		else if (ks == XK_r)
			reset_progress(rend);
	}
	if (xev.type == ButtonPress)
	{
	    int mouse_x = xev.xbutton.x;
	    int mouse_y = xev.xbutton.y;
		float norm_x = (2.0f * mouse_x / rend->width) - 1.0f;
		float norm_y = 1.0f - (2.0f * mouse_y / rend->height);
	    int button = xev.xbutton.button;
		if (button == Button1)
			button_press(rend, norm_x, norm_y);
	}
	if (xev.type == ClientMessage)
    {
		if ((Atom)xev.xclient.data.l[0] == rend->wm_delete)
		{
			clean_rend(rend);
			return (1);
		}
    }

	return (0);
}

#include "skybox.h"

#include <stb_image.h>

#include "res/nx.h"
#include "res/ny.h"
#include "res/nz.h"
#include "res/px.h"
#include "res/py.h"
#include "res/pz.h"

void skybox::render()
{
    auto init = [](const uint8_t* buff, int length, rs2::texture_buffer& tex){
        int x, y, comp;
        auto data = stbi_load_from_memory(buff, length, &x, &y, &comp, 3);
        tex.upload_image(x, y, data, GL_RGB);
        stbi_image_free(data);
    };
    if (!initialized)
    {
        init(cubemap_pz_png_data, cubemap_pz_png_size, plus_z);
        init(cubemap_nz_png_data, cubemap_nz_png_size, minus_z);
        init(cubemap_nx_png_data, cubemap_nx_png_size, minus_x);
        init(cubemap_px_png_data, cubemap_px_png_size, plus_x);
        init(cubemap_py_png_data, cubemap_py_png_size, plus_y);
        init(cubemap_ny_png_data, cubemap_ny_png_size, minus_y);
        initialized = true;
    }
    glEnable(GL_TEXTURE_2D);

    glColor3f(1.f, 1.f, 1.f);

    const auto r = 50.f;
    const auto re = 49.999f;

    glBindTexture(GL_TEXTURE_2D, plus_z.get_gl_handle());
    glBegin(GL_QUAD_STRIP);
    {
        glTexCoord2f(0.f, 1.f); glVertex3f(-r, r, re);
        glTexCoord2f(0.f, 0.f); glVertex3f(-r, -r, re);
        glTexCoord2f(1.f, 1.f); glVertex3f(r, r, re);
        glTexCoord2f(1.f, 0.f); glVertex3f(r, -r, re);
    }
    glEnd();

    glBindTexture(GL_TEXTURE_2D, minus_z.get_gl_handle());
    glBegin(GL_QUAD_STRIP);
    {
        glTexCoord2f(1.f, 1.f); glVertex3f(-r, r, -re);
        glTexCoord2f(1.f, 0.f); glVertex3f(-r, -r, -re);
        glTexCoord2f(0.f, 1.f); glVertex3f(r, r, -re);
        glTexCoord2f(0.f, 0.f); glVertex3f(r, -r, -re);
    }
    glEnd();

    glBindTexture(GL_TEXTURE_2D, minus_x.get_gl_handle());
    glBegin(GL_QUAD_STRIP);
    {
        glTexCoord2f(1.f, 0.f); glVertex3f(-re, -r, r);
        glTexCoord2f(0.f, 0.f); glVertex3f(-re, -r, -r);
        glTexCoord2f(1.f, 1.f); glVertex3f(-re, r, r);
        glTexCoord2f(0.f, 1.f); glVertex3f(-re, r, -r);
    }
    glEnd();

    glBindTexture(GL_TEXTURE_2D, plus_x.get_gl_handle());
    glBegin(GL_QUAD_STRIP);
    {
        glTexCoord2f(0.f, 0.f); glVertex3f(re, -r, r);
        glTexCoord2f(1.f, 0.f); glVertex3f(re, -r, -r);
        glTexCoord2f(0.f, 1.f); glVertex3f(re, r, r);
        glTexCoord2f(1.f, 1.f); glVertex3f(re, r, -r);
    }
    glEnd();


    glBindTexture(GL_TEXTURE_2D, minus_y.get_gl_handle());
    glBegin(GL_QUAD_STRIP);
    {
        glTexCoord2f(0.f, 0.f); glVertex3f(-r, re, r);
        glTexCoord2f(0.f, 1.f); glVertex3f(-r, re, -r);
        glTexCoord2f(1.f, 0.f); glVertex3f(r,  re, r);
        glTexCoord2f(1.f, 1.f); glVertex3f(r,  re, -r);
    }
    glEnd();

    glBindTexture(GL_TEXTURE_2D, plus_y.get_gl_handle());
    glBegin(GL_QUAD_STRIP);
    {
        glTexCoord2f(0.f, 1.f); glVertex3f(-r, -re, r);
        glTexCoord2f(0.f, 0.f); glVertex3f(-r, -re, -r);
        glTexCoord2f(1.f, 1.f); glVertex3f(r,  -re, r);
        glTexCoord2f(1.f, 0.f); glVertex3f(r,  -re, -r);
    }
    glEnd();

    glBindTexture(GL_TEXTURE_2D, 0);

    glDisable(GL_TEXTURE_2D);
}
#define $this this
#define $(obj) ((obj->vt->setThis(obj)), *(obj->vt))
#undef $this

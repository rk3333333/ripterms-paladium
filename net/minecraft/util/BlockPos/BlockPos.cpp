#include "BlockPos.h"

BlockPos BlockPos::newObject(const Ripterms::Maths::Vector3d& vector, JNIEnv* env)
{
	return BlockPos
	(
		env->NewObject
		(
			BlockPosClass.get_jclass(env),
			BlockPosClass.getMethodID("<init>"),
			(jdouble)vector.x,
			(jdouble)vector.y,
			(jdouble)vector.z
		), env
	);
}

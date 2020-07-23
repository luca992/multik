package org.jetbrains.multik.core

@Suppress("NOTHING_TO_INLINE")
inline fun requireDimension(dim: DN, shapeSize: Int) {
    require(dim.d == shapeSize) { "Dimension doesn't match the size of the shape: dimension (${dim.d}) != $shapeSize shape size." }
}

@Suppress("NOTHING_TO_INLINE")
inline fun requireShapeEmpty(shape: IntArray) {
    require(shape.isNotEmpty()) { "Shape cannot be empty." }
}

@PublishedApi
@Suppress("NOTHING_TO_INLINE", "UNCHECKED_CAST")
internal inline fun <T : Number, D : DN> initNdarray(
    data: MemoryView<T>, offset: Int = 0,
    shape: IntArray,
    strides: IntArray = computeStrides(shape),
    dtype: DataType, dim: D
): Ndarray<T, D> = when (dim.d) {
    1 -> D1Array<T>(data = data, offset = offset, shape = shape, strides = strides, dtype = dtype) as Ndarray<T, D>
    2 -> D2Array<T>(data = data, offset = offset, shape = shape, strides = strides, dtype = dtype) as Ndarray<T, D>
    3 -> D3Array<T>(data = data, offset = offset, shape = shape, strides = strides, dtype = dtype) as Ndarray<T, D>
    4 -> D4Array<T>(data = data, offset = offset, shape = shape, strides = strides, dtype = dtype) as Ndarray<T, D>
    else -> Ndarray<T, D>(data = data, offset = offset, shape = shape, strides = strides, dtype = dtype, dim = dim)
}

fun computeStrides(shape: IntArray): IntArray = shape.clone().apply {
    this[this.lastIndex] = 1
    for (i in this.lastIndex - 1 downTo 0) {
        this[i] = this[i + 1] * shape[i + 1]
    }
}

@Suppress("NOTHING_TO_INLINE")
internal inline fun zeroNumber(dtype: DataType): Number = when (dtype.nativeCode) {
    1 -> 0.toByte()
    2 -> 0.toShort()
    3 -> 0
    4 -> 0L
    5 -> 0f
    6 -> 0.0
    else -> throw Exception("Type not defined.")
}

//todo (exception message)
@Suppress("IMPLICIT_CAST_TO_ANY")
inline fun <reified T : Number> Number.toPrimitiveType(): T = when (T::class) {
    Byte::class -> this.toByte()
    Short::class -> this.toShort()
    Int::class -> this.toInt()
    Long::class -> this.toLong()
    Float::class -> this.toFloat()
    Double::class -> this.toDouble()
    else -> throw Exception("Type not defined.")
} as T

@Suppress("IMPLICIT_CAST_TO_ANY", "NOTHING_TO_INLINE", "UNCHECKED_CAST")
inline fun <T : Number> Number.toPrimitiveType(dtype: DataType): T = when (dtype.nativeCode) {
    1 -> this.toByte()
    2 -> this.toShort()
    3 -> this.toInt()
    4 -> this.toLong()
    5 -> this.toFloat()
    6 -> this.toDouble()
    else -> throw Exception("Type not defined.")
} as T

public operator fun <T : Number> Number.compareTo(other: T): Int = (this - other).toInt()

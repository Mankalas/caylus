/**
 * @file   exceptions.hh
 * @author  <mankalas@localhost,>
 * @date   Sun Jan 11 15:51:28 2009
 *
 * @brief
 *
 *
 */

#ifndef EXCEPTIONS_HH
# define EXCEPTIONS_HH

class Exception
{

};

class NotEnoughDenierEx : public Exception
{
};

class OccupiedBuildingEx : public Exception
{
};

class UnactivableBuildingEx : public Exception
{
};

class NoBuildingEx : public Exception
{
};

class MemAllocError : public Exception
{
};

class ImageNotFound : public Exception
{
};

#endif //EXCEPTIONS_HH

#ifndef ECS_VIEW_HPP
#define ECS_VIEW_HPP


namespace Blast2D {
	template<typename... Components>
	class EntityView {

	public:

		template<typename Func>
		EntityView each(Func func) {

			func();
			return *this;
		}
	};
}

#endif // ECS_VIEW_HPP

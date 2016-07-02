# Container widgets

`libui-node` provide various widgets that could contains children and that layout them using different strategies.

* [UiWindow](window.md) - A OS native window that contains only one child.
* [UiForm](form.md) - organize children as labeled fields.
* [UiGrid](grid.md) - allow to specify size and position of each children.
* [UiVerticalBox](verticalbox.md) - stack its chidren vertically.
* [UiHorizontalBox](horizontalbox.md) - stack its chidren horizontally.
* [UiTab](tab.md) - show each chidren in a separate tab.
* [UiGroup](group.md) - provide a caption and visually group it's child.


There are actually some inconsistency between container implementation, that will be resolved in future version of `libui`.

They also share many concept:

### margined

A container with margined property set to `true` will display an empty border around its content area.

### padded

A container with padded property set to `true` will separate its children with an increased amount of vertical and/or horizontal space.

### stretchy

A widget appended to its container with `stretchy` argument `true` will increase its size when parent size change.

### append

Append method allows to insert children as last one of the container.

### insertAt

`insertAt` method allows to insert children in specified position within the container.

### deleteAt

`delete` method allows to remove children at specified position within the container.

### setChild

`setChild` method set the child widget of containers that contains only one (group, window).

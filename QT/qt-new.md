# QML
- The import statement imports a module in a specific version.
- Comments can be made using // for single line comments or /* */ for multi-line comments. Just like in
C/C++ and JavaScript
- Every QML file needs to have exactly one root element, like HTML
- An element is declared by its type followed by { }
- Elements can have properties, they are in the form ‘‘ name: value‘‘
- Arbitrary elements inside a QML document can be accessed by using their id (an unquoted identifier)
- Elements can be nested, meaning a parent element can have child elements. The parent element can be
accessed using the parent keyword

## deferent features
Let’s go through the different features of properties:
1. id is a very special property-like value, it is used to reference elements inside a QML file (called “document” in QML). The id is not a string type but rather an identifier and part of the QML syntax. An id
needs to be unique inside a document and it can’t be reset to a different value, nor may it be queried. (It
behaves much like a reference in the C++ world.)
2. A property can be set to a value, depending on its type. If no value is given for a property, an initial value
will be chosen. You need to consult the documentation of the particular element for more information about
the initial value of a property.
3. A property can depend on one or many other properties. This is called binding. A bound property is updated
when its dependent properties change. It works like a contract, in this case, the height should always be
two times the width.
4. Adding own properties to an element is done using the property qualifier followed by the type, the name
and the optional initial value (property <type> <name> : <value>). If no initial value is given
a system initial value is chosen.
Note: You can also declare one property to be the default property if no property name is given by
prepending the property declaration with the default keyword. This is used for example when you
add child elements, the child elements are added automatically to the default property children of type
list if they are visible elements.
5. Another important way of declaring properties is using the alias keyword (property alias
<name>: <reference>). The alias keyword allows us to forward a property of an object or an
object itself from within the type to an outer scope. We will use this technique later when defining components to export the inner properties or element ids to the root level. A property alias does not need a type, it
uses the type of the referenced property or object.
6. The text property depends on the custom property times of type int. The int based value is automatically converted to a string type. The expression itself is another example of binding and results in the
text being updated every time the times property changes.
7. Some properties are grouped properties. This feature is used when a property is more structured and related
properties should be grouped together. Another way of writing grouped properties is font { family:
"Ubuntu"; pixelSize: 24 }.
8. Some properties are attached to the element itself. This is done for global relevant elements which appear only once in the application (e.g. keyboard input). The writing is <Element>.<property>:
<value>.
9. For every property, you can provide a signal handler. This handler is called after the property changes. For
example, here we want to be notified whenever the height changes and use the built-in console to log a
message to the system

##  Item Element
Item is the base element for all visual elements as such all other visual elements inherits from Item. It doesn’t
paint anything by itself but defines all properties which are common across all visual elements:
| Group |  Properties
:-:| :-: |
Geometry | x and y to define the top-left position, width and height for the expansion of the element and also the z stacking order to lift elements up or down from their naturalordering |
Layout handling  | anchors (left, right, top, bottom, vertical and horizontal center) to position elementsrelative to other elements with their margins |
Key handling | attached Key and KeyNavigation properties to control key handling and the input focus property to enable key handling in the first place|
Transformation | scale  and rotate transformation and the generic transform property list for x,y,z transformation and their transformOrigin point
Visual | opacity to control transparency, visible to show/hide elements, clip to restrain paint operations to the element boundary and smooth to enhance the rendering quality| 
State definition |  states list property with the supported list of states and the current state property as also the transitions list property to animate state changes | 
- To better understand the different properties we will try to introduce them throughout this chapter in the context of
the element presented. Please remember these fundamental properties are available on every visual element and
work the same across these elements.
>>> Note: The Item element is often used as a container for other elements, similar to the div element in HTML.
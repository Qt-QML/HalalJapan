function createObject(sourceFile, parentObject) {
    var component = Qt.createComponent(sourceFile);

    if( component.status !== Component.Ready )
    {
        if( component.status === Component.Error )
            console.debug("Error:"+ component.errorString() );
        return; // or maybe throw
    }

    var guiObject = component.createObject(parentObject);

    if (guiObject === null) {
        console.log("Error creating object");
    }
    else {
        return guiObject
    }
}

function createComponent(sourceFile, parentObject) {
    return Qt.createComponent(sourceFile);
}

function cloneObject(objectToClone) {
    var clone = {};
    for (var attribute in objectToClone) {
        clone[attribute] = objectToClone[attribute];
    }
    return clone;
}


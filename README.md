# QHexTools

A collection of QtQuick components for viewing hex data

## Example Usage

```
        HexView {
            id: hv
            xmodel: my_data
            Layout.fillWidth: true
        }


        HexData {
            id: my_data
            filename: "/Users/James/dev/projects/QHexTools/photo.jpg"
        }
```

# react-native-filament-physics

[Bullet](https://github.com/bulletphysics/bullet3) physics for [react-native-filament](https://github.com/margelo/react-native-filament). A physics world steps natively on an Engine's render thread with every rendered frame, and rigid bodies can move entities without JS per frame.

```sh
npm i react-native-filament-physics
```

Install the same version as `react-native-filament`; the two packages share native code. On iOS, run `npx react-native spm` again afterwards.

```tsx
import type { Model } from 'react-native-filament'
import { useCylinderShape, useRigidBody, type PhysicsWorld } from 'react-native-filament-physics'

function Coin({ world, model }: { world: PhysicsWorld; model: Model }) {
  const shape = useCylinderShape(world, model.boundingBox.halfExtent, 'y')
  useRigidBody(world, shape == null ? undefined : { shape, mass: 1, position: [0, 3, 0], entity: model.rootEntity })
  return null
}
```

`useWorld(options)` creates a world for the closest `<FilamentScene>`.

Imperatively, create a world on the render thread with `Physics.createWorld(engine, options)`. See the [Physics guide](https://margelo.github.io/react-native-filament/docs/physics).

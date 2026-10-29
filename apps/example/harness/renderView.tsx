import React from 'react'
import { View } from 'react-native'
import { render } from 'react-native-harness'
import { NativeFilamentView, type FilamentView } from 'react-native-filament'

export function renderView(): Promise<FilamentView> {
  return new Promise((resolve) => {
    render(<NativeFilamentView style={{ width: 200, height: 200 }} hybridRef={resolve} />)
  })
}

export function renderViews(count: number): Promise<FilamentView[]> {
  return new Promise((resolve) => {
    const views = new Map<number, FilamentView>()
    const onView = (index: number, view: FilamentView) => {
      views.set(index, view)
      if (views.size === count) resolve(Array.from({ length: count }, (_, at) => views.get(at)!))
    }
    render(
      <View style={{ flexDirection: 'row', flexWrap: 'wrap' }}>
        {Array.from({ length: count }, (_, index) => (
          <NativeFilamentView key={index} style={{ width: 60, height: 60 }} hybridRef={(view) => onView(index, view)} />
        ))}
      </View>
    )
  })
}
